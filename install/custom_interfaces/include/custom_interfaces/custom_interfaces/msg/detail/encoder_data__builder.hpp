// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from custom_interfaces:msg/EncoderData.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__MSG__DETAIL__ENCODER_DATA__BUILDER_HPP_
#define CUSTOM_INTERFACES__MSG__DETAIL__ENCODER_DATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "custom_interfaces/msg/detail/encoder_data__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace custom_interfaces
{

namespace msg
{

namespace builder
{

class Init_EncoderData_timestamp
{
public:
  explicit Init_EncoderData_timestamp(::custom_interfaces::msg::EncoderData & msg)
  : msg_(msg)
  {}
  ::custom_interfaces::msg::EncoderData timestamp(::custom_interfaces::msg::EncoderData::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_interfaces::msg::EncoderData msg_;
};

class Init_EncoderData_right_ticks
{
public:
  explicit Init_EncoderData_right_ticks(::custom_interfaces::msg::EncoderData & msg)
  : msg_(msg)
  {}
  Init_EncoderData_timestamp right_ticks(::custom_interfaces::msg::EncoderData::_right_ticks_type arg)
  {
    msg_.right_ticks = std::move(arg);
    return Init_EncoderData_timestamp(msg_);
  }

private:
  ::custom_interfaces::msg::EncoderData msg_;
};

class Init_EncoderData_left_ticks
{
public:
  Init_EncoderData_left_ticks()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_EncoderData_right_ticks left_ticks(::custom_interfaces::msg::EncoderData::_left_ticks_type arg)
  {
    msg_.left_ticks = std::move(arg);
    return Init_EncoderData_right_ticks(msg_);
  }

private:
  ::custom_interfaces::msg::EncoderData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_interfaces::msg::EncoderData>()
{
  return custom_interfaces::msg::builder::Init_EncoderData_left_ticks();
}

}  // namespace custom_interfaces

#endif  // CUSTOM_INTERFACES__MSG__DETAIL__ENCODER_DATA__BUILDER_HPP_
