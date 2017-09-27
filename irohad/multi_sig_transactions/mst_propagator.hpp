/**
 * Copyright Soramitsu Co., Ltd. 2017 All Rights Reserved.
 * http://soramitsu.co.jp
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef IROHA_MST_PROPAGATOR_HPP
#define IROHA_MST_PROPAGATOR_HPP

#include <rxcpp/rx.hpp>
#include <memory>
#include <memory>
#include "multi_sig_transactions/storage/mst_state.hpp"
#include "model/transaction.hpp"

namespace iroha {
  class MstPropagator {
   public:

    /**
     * Propagate in network multi-signature transaction for signing by other participants
     * @param transaction - transaction for propagation
     */
    virtual void propagate_transaction(model::Transaction transaction) = 0;

    /**
     * Prove updating of state for handling status of signing
     */
    virtual rxcpp::observable<std::shared_ptr<MstState>> onStateUpdate() = 0;

    /**
     * Observable emit transactions that prepared to processing in system
     */
    virtual rxcpp::observable<std::shared_ptr<model::Transaction>> onPreparedTransactions();

    virtual ~MstPropagator() = default;

  };
} // namespace iroha

#endif //IROHA_MST_PROPAGATOR_HPP
