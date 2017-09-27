/*
Copyright Soramitsu Co., Ltd. 2016 All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#ifndef IROHA_ACCOUNT_HPP
#define IROHA_ACCOUNT_HPP

#include <common/types.hpp>
#include <string>

namespace iroha {
  namespace model {

    /**
     * Account Model
     */
    struct Account {

      /**
       * User name is used as unique identifier of an account
       */
      std::string account_id;
      /*
       * Account has only one domain.
       * Name of the domain of a account
       */
      std::string domain_name;

      /**
       * Minimum quorum of signatures need for transactions
       */
      uint32_t quorum;
    };
  }
}

#endif  // IROHA_ACCOUNT_HPP
