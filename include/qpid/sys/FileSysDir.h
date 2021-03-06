#ifndef QPID_SYS_FILE_SYS_DIR_H
#define QPID_SYS_FILE_SYS_DIR_H 1

/*
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

#include <string>
#include "qpid/sys/Compile.h"

namespace qpid {
namespace sys {

/**
 * @class FileSysDir
 *
 * Represents a filesystem directory accessible from the local host.
 * This class simply checks existence of, and creates, a directory. It could
 * be added to later to list contents, etc.
 */
class FileSysDir
{
    const std::string dirPath;

  public:

    FileSysDir (std::string path) : dirPath(path) {}
    ~FileSysDir () {}

    /**
     * Check to see if the directory exists and is a directory. Throws an
     * exception if there is an error checking existence or if the path
     * exists but is not a directory.
     *
     * @retval true if the path exists and is a directory.
     * @retval false if the path does not exist.
     */
	QPID_SYS_EXTERN bool exists (void) const;

	QPID_SYS_EXTERN void mkdir(void);

    typedef void Callback(const std::string&);

    /**
     * Call the Callback function for every regular file in the directory
     *
     * @param cb Callback function that receives the full path to the file
     */
	QPID_SYS_EXTERN void forEachFile(Callback cb) const;

    std::string getPath   () { return dirPath; }
};
 
}} // namespace qpid::sys

#endif  /*!QPID_SYS_FILE_SYS_DIR_H*/
