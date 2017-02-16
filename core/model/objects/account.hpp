/*
Copyright Soramitsu Co., Ltd. 2016 All Rights Reserved.
http://soramitsu.co.jp

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

#include <string>
#include <cstdint>
#include "asset.hpp"

namespace object {

    struct Account {
        std::string publicKey;
        std::string name;

        std::vector<Asset> assets;

        explicit Account(const Account* a):
            publicKey(a->publicKey),
            name(a->name),
            assets(a->assets)
        {}

        explicit Account():
            publicKey(""),
            name("")
        {}

        explicit Account(
            std::string publicKey,
            std::string name
        ):
            publicKey(std::move(publicKey)),
            name(std::move(name))
        {}

        explicit Account(
            std::string publicKey
        ):
            publicKey(std::move(publicKey))
        {}


        explicit Account(
            std::string publicKey,
            std::string name,
            std::vector<Asset> assets
        ):
            publicKey(std::move(publicKey)),
            name(std::move(name)),
            assets(assets)

        {}

    };

};  // namespace asset

#endif //IROHA_ACCOUNT_HPP
