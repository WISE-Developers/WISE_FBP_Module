// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ccwfgmFuel.proto

package ca.wise.fuel.proto;

public interface FuelAttributeOrBuilder extends
    // @@protoc_insertion_point(interface_extends:WISE.FuelProto.FuelAttribute)
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
   * <code>.WISE.FuelProto.SpreadParmsAttribute spreadParms = 3;</code>
   * @return Whether the spreadParms field is set.
   */
  boolean hasSpreadParms();
  /**
   * <code>.WISE.FuelProto.SpreadParmsAttribute spreadParms = 3;</code>
   * @return The spreadParms.
   */
  ca.wise.fuel.proto.SpreadParmsAttribute getSpreadParms();
  /**
   * <code>.WISE.FuelProto.SpreadParmsAttribute spreadParms = 3;</code>
   */
  ca.wise.fuel.proto.SpreadParmsAttributeOrBuilder getSpreadParmsOrBuilder();

  /**
   * <code>.WISE.FuelProto.FmcAttribute fmc = 4;</code>
   * @return Whether the fmc field is set.
   */
  boolean hasFmc();
  /**
   * <code>.WISE.FuelProto.FmcAttribute fmc = 4;</code>
   * @return The fmc.
   */
  ca.wise.fuel.proto.FmcAttribute getFmc();
  /**
   * <code>.WISE.FuelProto.FmcAttribute fmc = 4;</code>
   */
  ca.wise.fuel.proto.FmcAttributeOrBuilder getFmcOrBuilder();

  /**
   * <code>.WISE.FuelProto.TfcAttribute tfc = 5;</code>
   * @return Whether the tfc field is set.
   */
  boolean hasTfc();
  /**
   * <code>.WISE.FuelProto.TfcAttribute tfc = 5;</code>
   * @return The tfc.
   */
  ca.wise.fuel.proto.TfcAttribute getTfc();
  /**
   * <code>.WISE.FuelProto.TfcAttribute tfc = 5;</code>
   */
  ca.wise.fuel.proto.TfcAttributeOrBuilder getTfcOrBuilder();

  /**
   * <code>.WISE.FuelProto.IsfAttribute isf = 6;</code>
   * @return Whether the isf field is set.
   */
  boolean hasIsf();
  /**
   * <code>.WISE.FuelProto.IsfAttribute isf = 6;</code>
   * @return The isf.
   */
  ca.wise.fuel.proto.IsfAttribute getIsf();
  /**
   * <code>.WISE.FuelProto.IsfAttribute isf = 6;</code>
   */
  ca.wise.fuel.proto.IsfAttributeOrBuilder getIsfOrBuilder();

  /**
   * <code>.WISE.FuelProto.AccAlphaAttribute accAlpha = 7;</code>
   * @return Whether the accAlpha field is set.
   */
  boolean hasAccAlpha();
  /**
   * <code>.WISE.FuelProto.AccAlphaAttribute accAlpha = 7;</code>
   * @return The accAlpha.
   */
  ca.wise.fuel.proto.AccAlphaAttribute getAccAlpha();
  /**
   * <code>.WISE.FuelProto.AccAlphaAttribute accAlpha = 7;</code>
   */
  ca.wise.fuel.proto.AccAlphaAttributeOrBuilder getAccAlphaOrBuilder();

  /**
   * <code>.WISE.FuelProto.LbAttribute lb = 8;</code>
   * @return Whether the lb field is set.
   */
  boolean hasLb();
  /**
   * <code>.WISE.FuelProto.LbAttribute lb = 8;</code>
   * @return The lb.
   */
  ca.wise.fuel.proto.LbAttribute getLb();
  /**
   * <code>.WISE.FuelProto.LbAttribute lb = 8;</code>
   */
  ca.wise.fuel.proto.LbAttributeOrBuilder getLbOrBuilder();

  /**
   * <code>.WISE.FuelProto.DbhAttribute dbh = 9 [deprecated = true];</code>
   * @return Whether the dbh field is set.
   */
  @java.lang.Deprecated boolean hasDbh();
  /**
   * <code>.WISE.FuelProto.DbhAttribute dbh = 9 [deprecated = true];</code>
   * @return The dbh.
   */
  @java.lang.Deprecated ca.wise.fuel.proto.DbhAttribute getDbh();
  /**
   * <code>.WISE.FuelProto.DbhAttribute dbh = 9 [deprecated = true];</code>
   */
  @java.lang.Deprecated ca.wise.fuel.proto.DbhAttributeOrBuilder getDbhOrBuilder();

  /**
   * <code>.WISE.FuelProto.FlameLengthAttribute flameLength = 10;</code>
   * @return Whether the flameLength field is set.
   */
  boolean hasFlameLength();
  /**
   * <code>.WISE.FuelProto.FlameLengthAttribute flameLength = 10;</code>
   * @return The flameLength.
   */
  ca.wise.fuel.proto.FlameLengthAttribute getFlameLength();
  /**
   * <code>.WISE.FuelProto.FlameLengthAttribute flameLength = 10;</code>
   */
  ca.wise.fuel.proto.FlameLengthAttributeOrBuilder getFlameLengthOrBuilder();

  /**
   * <code>.WISE.FuelProto.RsiAttribute rsi = 11;</code>
   * @return Whether the rsi field is set.
   */
  boolean hasRsi();
  /**
   * <code>.WISE.FuelProto.RsiAttribute rsi = 11;</code>
   * @return The rsi.
   */
  ca.wise.fuel.proto.RsiAttribute getRsi();
  /**
   * <code>.WISE.FuelProto.RsiAttribute rsi = 11;</code>
   */
  ca.wise.fuel.proto.RsiAttributeOrBuilder getRsiOrBuilder();

  /**
   * <code>.WISE.FuelProto.SfcAttribute sfc = 12;</code>
   * @return Whether the sfc field is set.
   */
  boolean hasSfc();
  /**
   * <code>.WISE.FuelProto.SfcAttribute sfc = 12;</code>
   * @return The sfc.
   */
  ca.wise.fuel.proto.SfcAttribute getSfc();
  /**
   * <code>.WISE.FuelProto.SfcAttribute sfc = 12;</code>
   */
  ca.wise.fuel.proto.SfcAttributeOrBuilder getSfcOrBuilder();

  /**
   * <code>.WISE.FuelProto.CfbAttribute cfb = 13;</code>
   * @return Whether the cfb field is set.
   */
  boolean hasCfb();
  /**
   * <code>.WISE.FuelProto.CfbAttribute cfb = 13;</code>
   * @return The cfb.
   */
  ca.wise.fuel.proto.CfbAttribute getCfb();
  /**
   * <code>.WISE.FuelProto.CfbAttribute cfb = 13;</code>
   */
  ca.wise.fuel.proto.CfbAttributeOrBuilder getCfbOrBuilder();

  public ca.wise.fuel.proto.FuelAttribute.MsgCase getMsgCase();
}
