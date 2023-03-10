// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ccwfgmFuel.proto

package ca.wise.fuel.proto;

public interface CcwfgmFuelOrBuilder extends
    // @@protoc_insertion_point(interface_extends:WISE.FuelProto.CcwfgmFuel)
    com.google.protobuf.MessageOrBuilder {

  /**
   * <code>int32 version = 1;</code>
   * @return The version.
   */
  int getVersion();

  /**
   * <code>.WISE.FuelProto.FuelName readonly = 2;</code>
   * @return The enum numeric value on the wire for readonly.
   */
  int getReadonlyValue();
  /**
   * <code>.WISE.FuelProto.FuelName readonly = 2;</code>
   * @return The readonly.
   */
  ca.wise.fuel.proto.FuelName getReadonly();

  /**
   * <code>.WISE.FuelProto.CcwfgmFuel.FuelData data = 3;</code>
   * @return Whether the data field is set.
   */
  boolean hasData();
  /**
   * <code>.WISE.FuelProto.CcwfgmFuel.FuelData data = 3;</code>
   * @return The data.
   */
  ca.wise.fuel.proto.CcwfgmFuel.FuelData getData();
  /**
   * <code>.WISE.FuelProto.CcwfgmFuel.FuelData data = 3;</code>
   */
  ca.wise.fuel.proto.CcwfgmFuel.FuelDataOrBuilder getDataOrBuilder();

  /**
   * <pre>
   * not really optional but need to be able to suppress it in the old file format
   * </pre>
   *
   * <code>uint32 color = 4;</code>
   * @return Whether the color field is set.
   */
  boolean hasColor();
  /**
   * <pre>
   * not really optional but need to be able to suppress it in the old file format
   * </pre>
   *
   * <code>uint32 color = 4;</code>
   * @return The color.
   */
  int getColor();

  /**
   * <code>string comments = 5;</code>
   * @return Whether the comments field is set.
   */
  boolean hasComments();
  /**
   * <code>string comments = 5;</code>
   * @return The comments.
   */
  java.lang.String getComments();
  /**
   * <code>string comments = 5;</code>
   * @return The bytes for comments.
   */
  com.google.protobuf.ByteString
      getCommentsBytes();

  /**
   * <code>.WISE.FuelProto.CcwfgmFuel.Flags flags = 6;</code>
   * @return Whether the flags field is set.
   */
  boolean hasFlags();
  /**
   * <code>.WISE.FuelProto.CcwfgmFuel.Flags flags = 6;</code>
   * @return The flags.
   */
  ca.wise.fuel.proto.CcwfgmFuel.Flags getFlags();
  /**
   * <code>.WISE.FuelProto.CcwfgmFuel.Flags flags = 6;</code>
   */
  ca.wise.fuel.proto.CcwfgmFuel.FlagsOrBuilder getFlagsOrBuilder();

  public ca.wise.fuel.proto.CcwfgmFuel.MsgCase getMsgCase();
}
