// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from custom_interfaces:msg/EncoderData.idl
// generated code does not contain a copyright notice
#include "custom_interfaces/msg/detail/encoder_data__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
custom_interfaces__msg__EncoderData__init(custom_interfaces__msg__EncoderData * msg)
{
  if (!msg) {
    return false;
  }
  // left_ticks
  // right_ticks
  // timestamp
  return true;
}

void
custom_interfaces__msg__EncoderData__fini(custom_interfaces__msg__EncoderData * msg)
{
  if (!msg) {
    return;
  }
  // left_ticks
  // right_ticks
  // timestamp
}

bool
custom_interfaces__msg__EncoderData__are_equal(const custom_interfaces__msg__EncoderData * lhs, const custom_interfaces__msg__EncoderData * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // left_ticks
  if (lhs->left_ticks != rhs->left_ticks) {
    return false;
  }
  // right_ticks
  if (lhs->right_ticks != rhs->right_ticks) {
    return false;
  }
  // timestamp
  if (lhs->timestamp != rhs->timestamp) {
    return false;
  }
  return true;
}

bool
custom_interfaces__msg__EncoderData__copy(
  const custom_interfaces__msg__EncoderData * input,
  custom_interfaces__msg__EncoderData * output)
{
  if (!input || !output) {
    return false;
  }
  // left_ticks
  output->left_ticks = input->left_ticks;
  // right_ticks
  output->right_ticks = input->right_ticks;
  // timestamp
  output->timestamp = input->timestamp;
  return true;
}

custom_interfaces__msg__EncoderData *
custom_interfaces__msg__EncoderData__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  custom_interfaces__msg__EncoderData * msg = (custom_interfaces__msg__EncoderData *)allocator.allocate(sizeof(custom_interfaces__msg__EncoderData), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(custom_interfaces__msg__EncoderData));
  bool success = custom_interfaces__msg__EncoderData__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
custom_interfaces__msg__EncoderData__destroy(custom_interfaces__msg__EncoderData * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    custom_interfaces__msg__EncoderData__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
custom_interfaces__msg__EncoderData__Sequence__init(custom_interfaces__msg__EncoderData__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  custom_interfaces__msg__EncoderData * data = NULL;

  if (size) {
    data = (custom_interfaces__msg__EncoderData *)allocator.zero_allocate(size, sizeof(custom_interfaces__msg__EncoderData), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = custom_interfaces__msg__EncoderData__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        custom_interfaces__msg__EncoderData__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
custom_interfaces__msg__EncoderData__Sequence__fini(custom_interfaces__msg__EncoderData__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      custom_interfaces__msg__EncoderData__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

custom_interfaces__msg__EncoderData__Sequence *
custom_interfaces__msg__EncoderData__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  custom_interfaces__msg__EncoderData__Sequence * array = (custom_interfaces__msg__EncoderData__Sequence *)allocator.allocate(sizeof(custom_interfaces__msg__EncoderData__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = custom_interfaces__msg__EncoderData__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
custom_interfaces__msg__EncoderData__Sequence__destroy(custom_interfaces__msg__EncoderData__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    custom_interfaces__msg__EncoderData__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
custom_interfaces__msg__EncoderData__Sequence__are_equal(const custom_interfaces__msg__EncoderData__Sequence * lhs, const custom_interfaces__msg__EncoderData__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!custom_interfaces__msg__EncoderData__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
custom_interfaces__msg__EncoderData__Sequence__copy(
  const custom_interfaces__msg__EncoderData__Sequence * input,
  custom_interfaces__msg__EncoderData__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(custom_interfaces__msg__EncoderData);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    custom_interfaces__msg__EncoderData * data =
      (custom_interfaces__msg__EncoderData *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!custom_interfaces__msg__EncoderData__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          custom_interfaces__msg__EncoderData__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!custom_interfaces__msg__EncoderData__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
