// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rsi.proto

package ca.wise.fuel.proto;

public interface RsiC6OrBuilder extends
    // @@protoc_insertion_point(interface_extends:WISE.FuelProto.RsiC6)
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
   * <code>.WISE.FuelProto.RsiC6.Parms parms = 3;</code>
   * @return Whether the parms field is set.
   */
  boolean hasParms();
  /**
   * <code>.WISE.FuelProto.RsiC6.Parms parms = 3;</code>
   * @return The parms.
   */
  ca.wise.fuel.proto.RsiC6.Parms getParms();
  /**
   * <code>.WISE.FuelProto.RsiC6.Parms parms = 3;</code>
   */
  ca.wise.fuel.proto.RsiC6.ParmsOrBuilder getParmsOrBuilder();

  public ca.wise.fuel.proto.RsiC6.MsgCase getMsgCase();
}
