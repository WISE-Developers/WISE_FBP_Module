// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ccwfgmFuel.proto

package ca.wise.fuel.proto;

public interface SpreadParmsMixedOrBuilder extends
    // @@protoc_insertion_point(interface_extends:WISE.FuelProto.SpreadParmsMixed)
    com.google.protobuf.MessageOrBuilder {

  /**
   * <code>int32 version = 1;</code>
   * @return The version.
   */
  int getVersion();

  /**
   * <code>.WISE.FuelProto.SpreadParmsMixed.DefaultParms default = 2;</code>
   * @return Whether the default field is set.
   */
  boolean hasDefault();
  /**
   * <code>.WISE.FuelProto.SpreadParmsMixed.DefaultParms default = 2;</code>
   * @return The default.
   */
  ca.wise.fuel.proto.SpreadParmsMixed.DefaultParms getDefault();
  /**
   * <code>.WISE.FuelProto.SpreadParmsMixed.DefaultParms default = 2;</code>
   */
  ca.wise.fuel.proto.SpreadParmsMixed.DefaultParmsOrBuilder getDefaultOrBuilder();

  /**
   * <code>.WISE.FuelProto.SpreadParmsMixed.Parms parms = 3;</code>
   * @return Whether the parms field is set.
   */
  boolean hasParms();
  /**
   * <code>.WISE.FuelProto.SpreadParmsMixed.Parms parms = 3;</code>
   * @return The parms.
   */
  ca.wise.fuel.proto.SpreadParmsMixed.Parms getParms();
  /**
   * <code>.WISE.FuelProto.SpreadParmsMixed.Parms parms = 3;</code>
   */
  ca.wise.fuel.proto.SpreadParmsMixed.ParmsOrBuilder getParmsOrBuilder();

  public ca.wise.fuel.proto.SpreadParmsMixed.MsgCase getMsgCase();
}
