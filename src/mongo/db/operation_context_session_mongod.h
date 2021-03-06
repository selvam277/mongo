/*
 *    Copyright (C) 2018 MongoDB, Inc.
 *
 *    This program is free software: you can redistribute it and/or  modify
 *    it under the terms of the GNU Affero General Public License, version 3,
 *    as published by the Free Software Foundation.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Affero General Public License for more details.
 *
 *    You should have received a copy of the GNU Affero General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *    As a special exception, the copyright holders give permission to link the
 *    code of portions of this program with the OpenSSL library under certain
 *    conditions as described in each individual source file and distribute
 *    linked combinations including the program with the OpenSSL library. You
 *    must comply with the GNU Affero General Public License in all respects for
 *    all of the code used other than as permitted herein. If you modify file(s)
 *    with this exception, you may extend this exception to your version of the
 *    file(s), but you are not obligated to do so. If you do not wish to do so,
 *    delete this exception statement from your version. If you delete this
 *    exception statement from all source files in the program, then also delete
 *    it in the license file.
 */

#pragma once

#include <boost/optional.hpp>

#include "mongo/db/session_catalog.h"

namespace mongo {

class OperationContext;

/**
 * Scoped object, which checks out the session specified in the passed operation context and stores
 * it for later access by the command. The session is installed at construction time and is removed
 * at destruction.
 */
class OperationContextSessionMongod {
public:
    OperationContextSessionMongod(OperationContext* opCtx,
                                  bool shouldCheckOutSession,
                                  boost::optional<bool> autocommit,
                                  boost::optional<bool> startTransaction,
                                  boost::optional<bool> coordinator = boost::none);

private:
    OperationContextSession _operationContextSession;
};

/**
 * Similar to OperationContextSessionMongod, but this starts a new transaction unconditionally
 * without refreshing the state from disk. The session reloads the state from disk but
 * the transaction participant will not use the on-disk state to refresh its in-memory state.
 *
 * This is used for transaction secondary application and recovery.
 */
class OperationContextSessionMongodWithoutRefresh {
public:
    OperationContextSessionMongodWithoutRefresh(OperationContext* opCtx);

private:
    OperationContextSession _operationContextSession;
};

}  // namespace mongo
