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

#include <grpc++/grpc++.h>
#include <gtest/gtest.h>
#include <atomic>
#include <crypto/crypto.hpp>
#include <peer_service/service.hpp>
#include <thread>
#define NPEERS 4

using namespace iroha;

class Service : public testing::Test {
 public:
  Service() {
    std::vector<ed25519::keypair_t> kps(NPEERS);
    std::generate_n(kps.begin(), NPEERS,
                    []() { return create_keypair(create_seed()); });

    std::vector<peerservice::Node> cluster;
    for (int i = 0; i < NPEERS; i++) {
      peerservice::Node node;
      node.ip = "127.0.0.1";
      node.port = (uint16_t)(65530 + i);
      node.pubkey = kps[i].pubkey;
      cluster.push_back(node);
    }

    for (int i = 0; i < NPEERS; i++) {
      auto &&builder = std::make_unique<grpc::ServerBuilder>();
      auto on = cluster[i].ip + ":" + std::to_string(cluster[i].port);

      printf("LISTEN ON: %s\n", on.c_str());

      builder->AddListeningPort(on, grpc::InsecureServerCredentials());

      auto &&loop = uvw::Loop::getDefault();
      auto &&service = std::make_unique<peerservice::PeerServiceImpl>(
          cluster, cluster[i].pubkey, loop);

      builder->RegisterService(service.get());

      auto &&pair = std::make_pair(std::move(builder), std::move(service));

      this->services.push_back(std::move(pair));

      // run each service with own event loop and within one thread
      std::thread([this]() {
        auto &&back = this->services.back();
        auto &&server = back.first->BuildAndStart();
        server->Wait();
      }).detach();
    }
  }

  std::vector<std::pair<std::unique_ptr<grpc::ServerBuilder>,
                        std::unique_ptr<peerservice::PeerServiceImpl>>>
      services;
};

TEST_F(Service, AyoungerThanB) {
  auto &&A = services[0].second;
  auto &&B = services[1].second;

  using peerservice::Heartbeat;
  using ENewLedger = peerservice::PeerServiceImpl::ENewLedger;

  size_t HEIGHT = 3;

  Heartbeat a;
  a.set_height(HEIGHT - 1);  // smaller than HEIGHT, A's ledger has less blocks
  Heartbeat b;
  b.set_height(HEIGHT);

  A->setMyState(a);
  B->setMyState(b);

  A->ping();

  // buggy:
  // auto online = A->getOnlineNodes();
  // EXPECT_EQ(online.size(), NPEERS) << "not all peers online";

  EXPECT_TRUE(A->getLoop()->alive()) << "A's loop is dead";
  EXPECT_TRUE(B->getLoop()->alive()) << "B's loop is dead";

  ASSERT_EQ(B->getLatestState().height(), HEIGHT);
  ASSERT_EQ(A->getLatestState().height(), HEIGHT)
      << "A(2) -> B(3) and  A did not update its latest state";
}