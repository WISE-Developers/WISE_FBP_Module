// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: accAlpha.proto

package ca.wise.fuel.proto;

public interface AccAlphaOpenOrBuilder extends
    // @@protoc_insertion_point(interface_extends:WISE.FuelProto.AccAlphaOpen)
    com.google.protobuf.MessageOrBuilder {

  /**
   * <code>int32 version = 1;</code>
   * @return The version.
   */
  int getVersion();

  /**
   * <code>.WISE.FuelProto.FuelName default = 2;</code>
   * @return The enum numeric value on the wire for default.
   */
  int getDefaultValue();
  /**
   * <code>.WISE.FuelProto.FuelName default = 2;</code>
   * @return The default.
   */
  ca.wise.fuel.proto.FuelName getDefault();

  /**
   * <code>.WISE.FuelProto.AccAlphaOpen.Parms parms = 3;</code>
   * @return Whether the parms field is set.
   */
  boolean hasParms();
  /**
   * <code>.WISE.FuelProto.AccAlphaOpen.Parms parms = 3;</code>
   * @return The parms.
   */
  ca.wise.fuel.proto.AccAlphaOpen.Parms getParms();
  /**
   * <code>.WISE.FuelProto.AccAlphaOpen.Parms parms = 3;</code>
   */
  ca.wise.fuel.proto.AccAlphaOpen.ParmsOrBuilder getParmsOrBuilder();

  public ca.wise.fuel.proto.AccAlphaOpen.MsgCase getMsgCase();
}