#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to custom_interfaces__msg__EncoderData

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct EncoderData {

    // This member is not documented.
    #[allow(missing_docs)]
    pub left_ticks: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub right_ticks: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub timestamp: u32,

}



impl Default for EncoderData {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::EncoderData::default())
  }
}

impl rosidl_runtime_rs::Message for EncoderData {
  type RmwMsg = super::msg::rmw::EncoderData;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        left_ticks: msg.left_ticks,
        right_ticks: msg.right_ticks,
        timestamp: msg.timestamp,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      left_ticks: msg.left_ticks,
      right_ticks: msg.right_ticks,
      timestamp: msg.timestamp,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      left_ticks: msg.left_ticks,
      right_ticks: msg.right_ticks,
      timestamp: msg.timestamp,
    }
  }
}


