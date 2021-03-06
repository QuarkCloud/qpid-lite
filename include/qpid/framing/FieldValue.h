#ifndef QPID_FRAMING_FIELD_VALUE_H
#define QPID_FRAMING_FIELD_VALUE_H 1
/*
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */

#include "qpid/sys/Exception.h"
#include "qpid/framing/amqp_types.h"
#include "qpid/framing/Buffer.h"
#include "qpid/framing/FieldTable.h"
#include "qpid/framing/Endian.h"
#include "qpid/framing/Compile.h"

#include <iostream>
#include <memory>
#include <vector>

#include <assert.h>

namespace qpid {
namespace framing {

/**
 * Exception that is the base exception for all field table errors.
 *
 * \ingroup clientapi
 */
class QPID_FRAMING_CLASS_EXTERN FieldValueException : public qpid::sys::Exception {};

/**
 * Exception thrown when we can't perform requested conversion
 *
 * \ingroup clientapi
 */
struct QPID_FRAMING_CLASS_EXTERN InvalidConversionException : public FieldValueException {
    InvalidConversionException() {}
};

class List;

/**
 * Value that can appear in an AMQP field table
 *
 * \ingroup clientapi
 */
class QPID_FRAMING_CLASS_EXTERN FieldValue {
  public:
    /*
     * Abstract type for content of different types
     */
    class Data {
      public:
        virtual ~Data() {}
        virtual uint32_t encodedSize() const = 0;
        virtual void encode(Buffer& buffer) = 0;
        virtual void decode(Buffer& buffer) = 0;
        virtual bool operator==(const Data&) const = 0;

        virtual bool convertsToInt() const { return false; }
        virtual bool convertsToFloat() const { return false; }
        virtual bool convertsToString() const { return false; }
        virtual int64_t getInt() const { throw InvalidConversionException();}
        virtual double getFloat() const { throw InvalidConversionException();}
        virtual std::string getString() const { throw InvalidConversionException(); }

        virtual void print(std::ostream& out) const = 0;
    };

    FieldValue(): data(0) {};
    // Default assignment operator is fine
    void setType(uint8_t type);
    QPID_FRAMING_EXTERN uint8_t getType() const;
    Data& getData() { return *data; }
    uint32_t encodedSize() const { return 1 + data->encodedSize(); };
    bool empty() const { return data.get() == 0; }
    void encode(Buffer& buffer);
    void decode(Buffer& buffer);
    QPID_FRAMING_EXTERN bool operator==(const FieldValue&) const;
    QPID_FRAMING_INLINE_EXTERN bool operator!=(const FieldValue& v) const { return !(*this == v); }

    QPID_FRAMING_EXTERN void print(std::ostream& out) const;

    template <typename T> bool convertsTo() const { return false; }
    template <typename T> T get() const { throw InvalidConversionException(); }

    template <class T, int W> T getIntegerValue() const;
    template <class T> T getIntegerValue() const;
    template <class T, int W> T getFloatingPointValue() const;
    template <int W> void getFixedWidthValue(unsigned char*) const;
    template <class T> bool get(T&) const;

  protected:
    FieldValue(uint8_t t, Data* d): typeOctet(t), data(d) {}

  private:
    uint8_t typeOctet;
    std::auto_ptr<Data> data;
};

template <>
inline bool FieldValue::convertsTo<int>() const { return data->convertsToInt(); }

template <>
inline bool FieldValue::convertsTo<int64_t>() const { return data->convertsToInt(); }

template <>
inline bool FieldValue::convertsTo<std::string>() const { return data->convertsToString(); }

template <>
inline bool FieldValue::convertsTo<float>() const { return data->convertsToFloat(); }

template <>
inline bool FieldValue::convertsTo<double>() const { return data->convertsToFloat(); }

template <>
inline int FieldValue::get<int>() const { return static_cast<int>(data->getInt()); }

template <>
inline int64_t FieldValue::get<int64_t>() const { return data->getInt(); }

template <>
inline float FieldValue::get<float>() const { return (float)data->getFloat(); }

template <>
inline double FieldValue::get<double>() const { return data->getFloat(); }

template <>
inline std::string FieldValue::get<std::string>() const { return data->getString(); }

inline std::ostream& operator<<(std::ostream& out, const FieldValue& v) {
    v.print(out);
    return out;
}

template <int width>
class FixedWidthValue : public FieldValue::Data {
  protected:
    uint8_t octets[width];

  public:
    FixedWidthValue() {}
    FixedWidthValue(const uint8_t (&data)[width]) : octets(data) {}
    FixedWidthValue(const uint8_t* const data) { std::copy(data, data + width, octets); }

    uint32_t encodedSize() const { return width; }
    void encode(Buffer& buffer) { buffer.putRawData(octets, width); }
    void decode(Buffer& buffer) { buffer.getRawData(octets, width); }
    bool operator==(const Data& d) const {
        const FixedWidthValue<width>* rhs = dynamic_cast< const FixedWidthValue<width>* >(&d);
        if (rhs == 0) return false;
        else return std::equal(&octets[0], &octets[width], &rhs->octets[0]);
    }
    uint8_t* rawOctets() { return octets; }
    const uint8_t* rawOctets() const { return octets; }

    void print(std::ostream& o) const { o << "F" << width << ":"; };
};

template <class T> class FixedWidthIntValue : public FixedWidthValue<sizeof(T)> {
  public:
    FixedWidthIntValue(T v = 0) { endian::encodeInt(this->octets, v); }
    bool convertsToInt() const { return true; }
    int64_t getInt() const { return endian::decodeInt<T>(this->octets); }
    bool convertsToFloat() const { return true; }
    double getFloat() const { return (double)getInt(); }
};

// Explicitly specialise width 1 variants to avoid using the byte swapping code
template<> inline FixedWidthIntValue<bool>::FixedWidthIntValue(bool v) { this->octets[0] = v; }
template<> inline FixedWidthIntValue<int8_t>::FixedWidthIntValue(int8_t v) { this->octets[0] = v; }
template<> inline FixedWidthIntValue<uint8_t>::FixedWidthIntValue(uint8_t v) { this->octets[0] = v; }

template<> inline int64_t FixedWidthIntValue<bool>::getInt() const { return this->octets[0]; }
template<> inline int64_t FixedWidthIntValue<int8_t>::getInt() const { return this->octets[0]; }
template<> inline int64_t FixedWidthIntValue<uint8_t>::getInt() const { return this->octets[0]; }

template <class T> class FixedWidthFloatValue : public FixedWidthValue<sizeof(T)> {
  public:
    FixedWidthFloatValue(T v = 0) { endian::encodeFloat(this->octets, v); }
    bool convertsToFloat() const { return true; }
    double getFloat() const { return endian::decodeFloat<T>(this->octets); }
};

class UuidData : public FixedWidthValue<16> {
  public:
    UuidData();
    UuidData(const unsigned char* bytes);
    bool convertsToString() const;
    std::string getString() const;
};

template <class T, int W>
inline T FieldValue::getIntegerValue() const
{
    FixedWidthValue<W>* const fwv = dynamic_cast< FixedWidthValue<W>* const>(data.get());
    if (fwv) {
        return endian::decodeInt<T>(fwv->rawOctets());
    } else {
        throw InvalidConversionException();
    }
}

template <class T>
inline T FieldValue::getIntegerValue() const
{
    FixedWidthValue<1>* const fwv = dynamic_cast< FixedWidthValue<1>* const>(data.get());
    if (fwv) {
        uint8_t* octets = fwv->rawOctets();
        return octets[0];
    } else {
        throw InvalidConversionException();
    }
}

template <class T, int W>
inline T FieldValue::getFloatingPointValue() const {
    const FixedWidthFloatValue<T>* fv = dynamic_cast<FixedWidthFloatValue<T>*>(data.get());
    if (fv) {
        return endian::decodeFloat<T>(fv->rawOctets());
    } else {
        throw InvalidConversionException();
    }
}

template <int W> void FieldValue::getFixedWidthValue(unsigned char* value) const
{
    FixedWidthValue<W>* const fwv = dynamic_cast< FixedWidthValue<W>* const>(data.get());
    if (fwv) {
        std::copy(fwv->rawOctets(), fwv->rawOctets() + W, value);
    } else {
        throw InvalidConversionException();
    }
}

template <>
class FixedWidthValue<0> : public FieldValue::Data {
  public:
    // Implicit default constructor is fine
    uint32_t encodedSize() const { return 0; }
    void encode(Buffer&) {};
    void decode(Buffer&) {};
    bool operator==(const Data& d) const {
        const FixedWidthValue<0>* rhs = dynamic_cast< const FixedWidthValue<0>* >(&d);
        return rhs != 0;
    }
    void print(std::ostream& o) const { o << "F0"; };
};

template <int lenwidth>
class VariableWidthValue : public FieldValue::Data {
    std::vector<uint8_t> octets;

  public:
    VariableWidthValue() {}
    VariableWidthValue(const std::vector<uint8_t>& data) : octets(data) {}
    VariableWidthValue(const uint8_t* start, const uint8_t* end) : octets(start, end) {}
    uint32_t encodedSize() const { return lenwidth + octets.size(); }
    void encode(Buffer& buffer) {
        buffer.putUInt<lenwidth>(octets.size());
        if (octets.size() > 0)
            buffer.putRawData(&octets[0], octets.size());
    };
    void decode(Buffer& buffer) {
        uint32_t len = (uint32_t)buffer.getUInt<lenwidth>();
        buffer.checkAvailable(len);
        octets.resize(len);
        if (len > 0)
            buffer.getRawData(&octets[0], len);
    }
    bool operator==(const Data& d) const {
        const VariableWidthValue<lenwidth>* rhs = dynamic_cast< const VariableWidthValue<lenwidth>* >(&d);
        if (rhs == 0) return false;
        else return octets==rhs->octets;
    }

    bool convertsToString() const { return true; }
    std::string getString() const { return std::string(octets.begin(), octets.end()); }

    void print(std::ostream& o) const { o << "V" << lenwidth << ":" << octets.size() << ":"; };
};

template <class T>
class EncodedValue : public FieldValue::Data {
    T value;
  public:

    EncodedValue() {}
    EncodedValue(const T& v) : value(v) {}

    T& getValue() { return value; }
    const T& getValue() const { return value; }

    uint32_t encodedSize() const { return value.encodedSize(); }

    void encode(Buffer& buffer) {
        value.encode(buffer);
    };
    void decode(Buffer& buffer) {
        value.decode(buffer);
    }
    bool operator==(const Data& d) const {
        const EncodedValue<T>* rhs = dynamic_cast< const EncodedValue<T>* >(&d);
        if (rhs == 0) return false;
        else return value==rhs->value;
    }

    void print(std::ostream& o) const { o << "[" << value << "]"; };
};

/**
 * Accessor that can be used to get values of type FieldTable, Array
 * and List.
 */
template <class T>
inline bool FieldValue::get(T& t) const
{
    const EncodedValue<T>* v = dynamic_cast< EncodedValue<T>* >(data.get());    
    if (v != 0) {
        t = v->getValue();
        return true;
    } else {
        try {
            t = get<T>();
            return true;
        } catch (const InvalidConversionException&) {
            return false;
        }
    }
}

class Str8Value : public FieldValue {
  public:
    QPID_FRAMING_EXTERN Str8Value(const std::string& v);
};

class Str16Value : public FieldValue {
  public:
    QPID_FRAMING_EXTERN Str16Value(const std::string& v);
};

class Var16Value : public FieldValue {
  public:
    QPID_FRAMING_EXTERN Var16Value(const std::string& v, uint8_t code);
};

class Var32Value : public FieldValue {
  public:
    QPID_FRAMING_EXTERN Var32Value(const std::string& v, uint8_t code);
 };

class Struct32Value : public FieldValue {
  public:
    QPID_FRAMING_EXTERN Struct32Value(const std::string& v);
};

class FloatValue : public FieldValue
{
  public:
    QPID_FRAMING_EXTERN FloatValue(float f);
};
class DoubleValue : public FieldValue
{
  public:
    QPID_FRAMING_EXTERN DoubleValue(double f);
};

/*
 * Basic integer value encodes as signed 32 bit
 */
class IntegerValue : public FieldValue {
  public:
    QPID_FRAMING_EXTERN IntegerValue(int v);
};

class TimeValue : public FieldValue {
  public:
    QPID_FRAMING_EXTERN TimeValue(uint64_t v);
};

class Integer64Value : public FieldValue {
  public:
    QPID_FRAMING_EXTERN Integer64Value(int64_t v);
};

class Unsigned64Value : public FieldValue {
  public:
    QPID_FRAMING_EXTERN Unsigned64Value(uint64_t v);
};

class FieldTableValue : public FieldValue {
  public:
    typedef FieldTable ValueType;
    QPID_FRAMING_EXTERN FieldTableValue(const FieldTable&);
};

class ArrayValue : public FieldValue {
  public:
    QPID_FRAMING_EXTERN ArrayValue(const Array&);
};

class VoidValue : public FieldValue {
  public:
    QPID_FRAMING_EXTERN VoidValue();
};

class BoolValue : public FieldValue {
  public:
    QPID_FRAMING_EXTERN BoolValue(bool);
};

class Unsigned8Value : public FieldValue {
  public:
    QPID_FRAMING_EXTERN Unsigned8Value(uint8_t);
};

class Unsigned16Value : public FieldValue {
  public:
    QPID_FRAMING_EXTERN Unsigned16Value(uint16_t);
};

class Unsigned32Value : public FieldValue {
  public:
    QPID_FRAMING_EXTERN Unsigned32Value(uint32_t);
};

class Integer8Value : public FieldValue {
  public:
    QPID_FRAMING_EXTERN Integer8Value(int8_t);
};

class Integer16Value : public FieldValue {
  public:
    QPID_FRAMING_EXTERN Integer16Value(int16_t);
};

typedef IntegerValue Integer32Value;

class ListValue : public FieldValue {
  public:
    typedef List ValueType;
    QPID_FRAMING_EXTERN ListValue(const List&);
};

class UuidValue : public FieldValue {
  public:
    QPID_FRAMING_EXTERN UuidValue();
    QPID_FRAMING_EXTERN UuidValue(const unsigned char*);
};

template <class T>
bool getEncodedValue(FieldTable::ValuePtr vptr, T& value)
{
    if (vptr) {
        const EncodedValue<T>* ev = dynamic_cast< EncodedValue<T>* >(&(vptr->getData()));
        if (ev != 0) {
            value = ev->getValue();
            return true;
        }
    }
    return false;
}

}} // qpid::framing

#endif /** QPID_FRAMING_FIELD_VALUE_H */
