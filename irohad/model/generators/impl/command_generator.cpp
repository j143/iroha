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

#include "model/generators/command_generator.hpp"
#include "model/commands/add_asset_quantity.hpp"
#include "model/commands/add_peer.hpp"
#include "model/commands/add_signatory.hpp"
#include "model/commands/create_account.hpp"
#include "model/commands/create_asset.hpp"
#include "model/commands/create_domain.hpp"
#include "model/commands/remove_signatory.hpp"
#include "model/commands/set_quorum.hpp"
#include "model/commands/subtract_asset_quantity.hpp"
#include "model/commands/transfer_asset.hpp"
#include "model/commands/create_role.hpp"
#include "model/commands/append_role.hpp"
#include "model/permissions.hpp"

using namespace generator;

namespace iroha {
  namespace model {
    namespace generators {

      std::shared_ptr<Command> CommandGenerator::generateAddPeer(
          const std::string &address, const ed25519::pubkey_t &key) {
        return generateCommand<AddPeer>(key, address);
      }

      std::shared_ptr<Command> CommandGenerator::generateAddSignatory(
          const std::string &account_id, const ed25519::pubkey_t &key) {
        return generateCommand<AddSignatory>(account_id, key);
      }

      std::shared_ptr<Command> CommandGenerator::generateRemoveSignatory(
          const std::string &account_id, const ed25519::pubkey_t &key) {
        return generateCommand<RemoveSignatory>(account_id, key);
      }

      std::shared_ptr<Command> CommandGenerator::generateCreateAccount(
          const std::string &account_name, const std::string &domain_id,
          const ed25519::pubkey_t &key) {
        return generateCommand<CreateAccount>(account_name, domain_id, key);
      }

      std::shared_ptr<Command> CommandGenerator::generateCreateDomain(
          const std::string &domain_name) {
        return generateCommand<CreateDomain>(domain_name);
      }

      std::shared_ptr<Command> CommandGenerator::generateCreateAsset(
          const std::string &asset_name, const std::string &domain_name,
          uint8_t precision) {
        return generateCommand<CreateAsset>(asset_name, domain_name, precision);
      }

      std::shared_ptr<Command> CommandGenerator::generateCreateAdminRole(std::string role_name) {
        std::set<std::string> perms = {
            can_create_domain,  can_add_signatory,  can_remove_signatory,
            can_set_quorum,     can_get_my_account, can_get_my_signatories,
            can_get_my_acc_ast, can_get_my_acc_txs};
        return std::make_shared<CreateRole>(role_name, perms);
      }
    

      std::shared_ptr<Command> CommandGenerator::generateAddAssetQuantity(
          const std::string &account_id, const std::string &asset_id, const Amount &amount) {
        return generateCommand<AddAssetQuantity>(account_id, asset_id, amount);
      }

      std::shared_ptr<Command> CommandGenerator::generateSetQuorum(
          const std::string &account_id, uint32_t quorum) {
        return generateCommand<SetQuorum>(account_id, quorum);
      }
    

      std::shared_ptr<Command> CommandGenerator::generateSubtractAssetQuantity(
          const std::string &account_id, const std::string &asset_id, const Amount &amount) {
        // TODO: implement
        return nullptr;
      }

      std::shared_ptr<Command> CommandGenerator::generateTransferAsset(
          const std::string &src_account, const std::string &dest_account,
          const std::string &asset_id, const Amount &amount) {
        return generateCommand<TransferAsset>(src_account, dest_account,
                                              asset_id, amount);
      }

    }  // namespace generators
  }    // namespace model
}  // namespace iroha
