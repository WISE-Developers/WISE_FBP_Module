// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ccwfgmFuel.proto

package ca.wise.fuel.proto;

public interface TfcAttributeOrBuilder extends
    // @@protoc_insertion_point(interface_extends:WISE.FuelProto.TfcAttribute)
    com.google.protobuf.MessageOrBuilder {

  /**
   * <code>int32 version = 1;</code>
   * @return The version.
   */
  int getVersion();

  /**
   * <code>int64 commonField = 2 [deprecated = true];</code>
   * @return The commonField.
   */
  @java.lang.Deprecated long getCommonField();

  /**
   * <code>.WISE.FuelProto.TfcC1 c1 = 3;</code>
   * @return Whether the c1 field is set.
   */
  boolean hasC1();
  /**
   * <code>.WISE.FuelProto.TfcC1 c1 = 3;</code>
   * @return The c1.
   */
  ca.wise.fuel.proto.TfcC1 getC1();
  /**
   * <code>.WISE.FuelProto.TfcC1 c1 = 3;</code>
   */
  ca.wise.fuel.proto.TfcC1OrBuilder getC1OrBuilder();

  /**
   * <code>.WISE.FuelProto.TfcD2 d2 = 4;</code>
   * @return Whether the d2 field is set.
   */
  boolean hasD2();
  /**
   * <code>.WISE.FuelProto.TfcD2 d2 = 4;</code>
   * @return The d2.
   */
  ca.wise.fuel.proto.TfcD2 getD2();
  /**
   * <code>.WISE.FuelProto.TfcD2 d2 = 4;</code>
   */
  ca.wise.fuel.proto.TfcD2OrBuilder getD2OrBuilder();

  /**
   * <code>.WISE.FuelProto.TfcM1 m1 = 5;</code>
   * @return Whether the m1 field is set.
   */
  boolean hasM1();
  /**
   * <code>.WISE.FuelProto.TfcM1 m1 = 5;</code>
   * @return The m1.
   */
  ca.wise.fuel.proto.TfcM1 getM1();
  /**
   * <code>.WISE.FuelProto.TfcM1 m1 = 5;</code>
   */
  ca.wise.fuel.proto.TfcM1OrBuilder getM1OrBuilder();

  /**
   * <code>.WISE.FuelProto.TfcO1 o1 = 6;</code>
   * @return Whether the o1 field is set.
   */
  boolean hasO1();
  /**
   * <code>.WISE.FuelProto.TfcO1 o1 = 6;</code>
   * @return The o1.
   */
  ca.wise.fuel.proto.TfcO1 getO1();
  /**
   * <code>.WISE.FuelProto.TfcO1 o1 = 6;</code>
   */
  ca.wise.fuel.proto.TfcO1OrBuilder getO1OrBuilder();

  public ca.wise.fuel.proto.TfcAttribute.MsgCase getMsgCase();
}