// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include <iostream>
using namespace std;
using std::placeholders::_1;

bool prime(int n){
  int i;
  bool is_prime = true;
  if (n == 0 || n == 1) {
    is_prime = false;
  }

  // loop to check if n is prime
  for (i = 2; i <= n/2; ++i) {
    if (n % i == 0) {
      is_prime = false;
      break;
    }
  }
  

  return is_prime;
}

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("minimal_subscriber")
  {
    subscription_ = this->create_subscription<std_msgs::msg::Int32>(
      "topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
  }




  
  
  void topic_callback(const std_msgs::msg::Int32 & msg) const
  {
    int n = msg.data;
    bool is_prime = prime(n);
    if(is_prime){
      RCLCPP_INFO(this->get_logger(), " %d is a Prime number" , n);
    }
    else{
      RCLCPP_INFO(this->get_logger(), "%d is a Composite number " , n);
    }
    
  }
  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
