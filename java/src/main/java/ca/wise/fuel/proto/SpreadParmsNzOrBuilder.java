// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: spreadParms.proto

package ca.wise.fuel.proto;

public interface SpreadParmsNzOrBuilder extends
    // @@protoc_insertion_point(interface_extends:WISE.FuelProto.SpreadParmsNz)
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
   * <code>.WISE.FuelProto.SpreadParmsNz.Parms parms = 3;</code>
   * @return Whether the parms field is set.
   */
  boolean hasParms();
  /**
   * <code>.WISE.FuelProto.SpreadParmsNz.Parms parms = 3;</code>
   * @return The parms.
   */
  ca.wise.fuel.proto.SpreadParmsNz.Parms getParms();
  /**
   * <code>.WISE.FuelProto.SpreadParmsNz.Parms parms = 3;</code>
   */
  ca.wise.fuel.proto.SpreadParmsNz.ParmsOrBuilder getParmsOrBuilder();

  public ca.wise.fuel.proto.SpreadParmsNz.MsgCase getMsgCase();
}