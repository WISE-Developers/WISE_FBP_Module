// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ccwfgmFuel.proto

package ca.wise.fuel.proto;

public interface FlameLengthAttributeOrBuilder extends
    // @@protoc_insertion_point(interface_extends:WISE.FuelProto.FlameLengthAttribute)
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
   * <code>.WISE.FuelProto.FlameLengthAlexander82 alexander82 = 3;</code>
   * @return Whether the alexander82 field is set.
   */
  boolean hasAlexander82();
  /**
   * <code>.WISE.FuelProto.FlameLengthAlexander82 alexander82 = 3;</code>
   * @return The alexander82.
   */
  ca.wise.fuel.proto.FlameLengthAlexander82 getAlexander82();
  /**
   * <code>.WISE.FuelProto.FlameLengthAlexander82 alexander82 = 3;</code>
   */
  ca.wise.fuel.proto.FlameLengthAlexander82OrBuilder getAlexander82OrBuilder();

  /**
   * <code>.WISE.FuelProto.FlameLengthAlexander82Tree alexander82Tree = 4;</code>
   * @return Whether the alexander82Tree field is set.
   */
  boolean hasAlexander82Tree();
  /**
   * <code>.WISE.FuelProto.FlameLengthAlexander82Tree alexander82Tree = 4;</code>
   * @return The alexander82Tree.
   */
  ca.wise.fuel.proto.FlameLengthAlexander82Tree getAlexander82Tree();
  /**
   * <code>.WISE.FuelProto.FlameLengthAlexander82Tree alexander82Tree = 4;</code>
   */
  ca.wise.fuel.proto.FlameLengthAlexander82TreeOrBuilder getAlexander82TreeOrBuilder();

  /**
   * <code>.WISE.FuelProto.FlameLengthTree tree = 5;</code>
   * @return Whether the tree field is set.
   */
  boolean hasTree();
  /**
   * <code>.WISE.FuelProto.FlameLengthTree tree = 5;</code>
   * @return The tree.
   */
  ca.wise.fuel.proto.FlameLengthTree getTree();
  /**
   * <code>.WISE.FuelProto.FlameLengthTree tree = 5;</code>
   */
  ca.wise.fuel.proto.FlameLengthTreeOrBuilder getTreeOrBuilder();

  /**
   * <code>.WISE.FuelProto.FlameLengthOther other = 6;</code>
   * @return Whether the other field is set.
   */
  boolean hasOther();
  /**
   * <code>.WISE.FuelProto.FlameLengthOther other = 6;</code>
   * @return The other.
   */
  ca.wise.fuel.proto.FlameLengthOther getOther();
  /**
   * <code>.WISE.FuelProto.FlameLengthOther other = 6;</code>
   */
  ca.wise.fuel.proto.FlameLengthOtherOrBuilder getOtherOrBuilder();

  public ca.wise.fuel.proto.FlameLengthAttribute.MsgCase getMsgCase();
}
