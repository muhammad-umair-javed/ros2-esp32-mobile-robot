// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from custom_interfaces:msg/EncoderData.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__MSG__DETAIL__ENCODER_DATA__STRUCT_HPP_
#define CUSTOM_INTERFACES__MSG__DETAIL__ENCODER_DATA__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__custom_interfaces__msg__EncoderData __attribute__((deprecated))
#else
# define DEPRECATED__custom_interfaces__msg__EncoderData __declspec(deprecated)
#endif

namespace custom_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct EncoderData_
{
  using Type = EncoderData_<ContainerAllocator>;

  explicit EncoderData_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->left_ticks = 0l;
      this->right_ticks = 0l;
      this->timestamp = 0ul;
    }
  }

  explicit EncoderData_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->left_ticks = 0l;
      this->right_ticks = 0l;
      this->timestamp = 0ul;
    }
  }

  // field types and members
  using _left_ticks_type =
    int32_t;
  _left_ticks_type left_ticks;
  using _right_ticks_type =
    int32_t;
  _right_ticks_type right_ticks;
  using _timestamp_type =
    uint32_t;
  _timestamp_type timestamp;

  // setters for named parameter idiom
  Type & set__left_ticks(
    const int32_t & _arg)
  {
    this->left_ticks = _arg;
    return *this;
  }
  Type & set__right_ticks(
    const int32_t & _arg)
  {
    this->right_ticks = _arg;
    return *this;
  }
  Type & set__timestamp(
    const uint32_t & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    custom_interfaces::msg::EncoderData_<ContainerAllocator> *;
  using ConstRawPtr =
    const custom_interfaces::msg::EncoderData_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<custom_interfaces::msg::EncoderData_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<custom_interfaces::msg::EncoderData_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      custom_interfaces::msg::EncoderData_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<custom_interfaces::msg::EncoderData_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      custom_interfaces::msg::EncoderData_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<custom_interfaces::msg::EncoderData_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<custom_interfaces::msg::EncoderData_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<custom_interfaces::msg::EncoderData_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__custom_interfaces__msg__EncoderData
    std::shared_ptr<custom_interfaces::msg::EncoderData_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__custom_interfaces__msg__EncoderData
    std::shared_ptr<custom_interfaces::msg::EncoderData_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const EncoderData_ & other) const
  {
    if (this->left_ticks != other.left_ticks) {
      return false;
    }
    if (this->right_ticks != other.right_ticks) {
      return false;
    }
    if (this->timestamp != other.timestamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const EncoderData_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct EncoderData_

// alias to use template instance with default allocator
using EncoderData =
  custom_interfaces::msg::EncoderData_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace custom_interfaces

#endif  // CUSTOM_INTERFACES__MSG__DETAIL__ENCODER_DATA__STRUCT_HPP_
