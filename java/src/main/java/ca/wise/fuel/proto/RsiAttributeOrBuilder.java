// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ccwfgmFuel.proto

package ca.wise.fuel.proto;

public interface RsiAttributeOrBuilder extends
    // @@protoc_insertion_point(interface_extends:WISE.FuelProto.RsiAttribute)
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
   * <code>.WISE.FuelProto.RsiC1 c1 = 3;</code>
   * @return Whether the c1 field is set.
   */
  boolean hasC1();
  /**
   * <code>.WISE.FuelProto.RsiC1 c1 = 3;</code>
   * @return The c1.
   */
  ca.wise.fuel.proto.RsiC1 getC1();
  /**
   * <code>.WISE.FuelProto.RsiC1 c1 = 3;</code>
   */
  ca.wise.fuel.proto.RsiC1OrBuilder getC1OrBuilder();

  /**
   * <code>.WISE.FuelProto.RsiC6 c6 = 4;</code>
   * @return Whether the c6 field is set.
   */
  boolean hasC6();
  /**
   * <code>.WISE.FuelProto.RsiC6 c6 = 4;</code>
   * @return The c6.
   */
  ca.wise.fuel.proto.RsiC6 getC6();
  /**
   * <code>.WISE.FuelProto.RsiC6 c6 = 4;</code>
   */
  ca.wise.fuel.proto.RsiC6OrBuilder getC6OrBuilder();

  /**
   * <code>.WISE.FuelProto.RsiD2 d2 = 5;</code>
   * @return Whether the d2 field is set.
   */
  boolean hasD2();
  /**
   * <code>.WISE.FuelProto.RsiD2 d2 = 5;</code>
   * @return The d2.
   */
  ca.wise.fuel.proto.RsiD2 getD2();
  /**
   * <code>.WISE.FuelProto.RsiD2 d2 = 5;</code>
   */
  ca.wise.fuel.proto.RsiD2OrBuilder getD2OrBuilder();

  /**
   * <code>.WISE.FuelProto.RsiM1 m1 = 6;</code>
   * @return Whether the m1 field is set.
   */
  boolean hasM1();
  /**
   * <code>.WISE.FuelProto.RsiM1 m1 = 6;</code>
   * @return The m1.
   */
  ca.wise.fuel.proto.RsiM1 getM1();
  /**
   * <code>.WISE.FuelProto.RsiM1 m1 = 6;</code>
   */
  ca.wise.fuel.proto.RsiM1OrBuilder getM1OrBuilder();

  /**
   * <code>.WISE.FuelProto.RsiM3 m3 = 7;</code>
   * @return Whether the m3 field is set.
   */
  boolean hasM3();
  /**
   * <code>.WISE.FuelProto.RsiM3 m3 = 7;</code>
   * @return The m3.
   */
  ca.wise.fuel.proto.RsiM3 getM3();
  /**
   * <code>.WISE.FuelProto.RsiM3 m3 = 7;</code>
   */
  ca.wise.fuel.proto.RsiM3OrBuilder getM3OrBuilder();

  /**
   * <code>.WISE.FuelProto.RsiM4 m4 = 8;</code>
   * @return Whether the m4 field is set.
   */
  boolean hasM4();
  /**
   * <code>.WISE.FuelProto.RsiM4 m4 = 8;</code>
   * @return The m4.
   */
  ca.wise.fuel.proto.RsiM4 getM4();
  /**
   * <code>.WISE.FuelProto.RsiM4 m4 = 8;</code>
   */
  ca.wise.fuel.proto.RsiM4OrBuilder getM4OrBuilder();

  /**
   * <code>.WISE.FuelProto.RsiO1 o1 = 9;</code>
   * @return Whether the o1 field is set.
   */
  boolean hasO1();
  /**
   * <code>.WISE.FuelProto.RsiO1 o1 = 9;</code>
   * @return The o1.
   */
  ca.wise.fuel.proto.RsiO1 getO1();
  /**
   * <code>.WISE.FuelProto.RsiO1 o1 = 9;</code>
   */
  ca.wise.fuel.proto.RsiO1OrBuilder getO1OrBuilder();

  /**
   * <code>.WISE.FuelProto.RsiConstant constant = 10;</code>
   * @return Whether the constant field is set.
   */
  boolean hasConstant();
  /**
   * <code>.WISE.FuelProto.RsiConstant constant = 10;</code>
   * @return The constant.
   */
  ca.wise.fuel.proto.RsiConstant getConstant();
  /**
   * <code>.WISE.FuelProto.RsiConstant constant = 10;</code>
   */
  ca.wise.fuel.proto.RsiConstantOrBuilder getConstantOrBuilder();

  public ca.wise.fuel.proto.RsiAttribute.MsgCase getMsgCase();
}
