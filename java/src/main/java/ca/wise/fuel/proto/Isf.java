// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: isf.proto

package ca.wise.fuel.proto;

public final class Isf {
  private Isf() {}
  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistryLite registry) {
  }

  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistry registry) {
    registerAllExtensions(
        (com.google.protobuf.ExtensionRegistryLite) registry);
  }
  static final com.google.protobuf.Descriptors.Descriptor
    internal_static_WISE_FuelProto_IsfC1_descriptor;
  static final 
    com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
      internal_static_WISE_FuelProto_IsfC1_fieldAccessorTable;
  static final com.google.protobuf.Descriptors.Descriptor
    internal_static_WISE_FuelProto_IsfC1_Parms_descriptor;
  static final 
    com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
      internal_static_WISE_FuelProto_IsfC1_Parms_fieldAccessorTable;
  static final com.google.protobuf.Descriptors.Descriptor
    internal_static_WISE_FuelProto_IsfM1_descriptor;
  static final 
    com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
      internal_static_WISE_FuelProto_IsfM1_fieldAccessorTable;
  static final com.google.protobuf.Descriptors.Descriptor
    internal_static_WISE_FuelProto_IsfM1_Parms_descriptor;
  static final 
    com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
      internal_static_WISE_FuelProto_IsfM1_Parms_fieldAccessorTable;
  static final com.google.protobuf.Descriptors.Descriptor
    internal_static_WISE_FuelProto_IsfM3M4_descriptor;
  static final 
    com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
      internal_static_WISE_FuelProto_IsfM3M4_fieldAccessorTable;
  static final com.google.protobuf.Descriptors.Descriptor
    internal_static_WISE_FuelProto_IsfM3M4_Parms_descriptor;
  static final 
    com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
      internal_static_WISE_FuelProto_IsfM3M4_Parms_fieldAccessorTable;
  static final com.google.protobuf.Descriptors.Descriptor
    internal_static_WISE_FuelProto_IsfO1_descriptor;
  static final 
    com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
      internal_static_WISE_FuelProto_IsfO1_fieldAccessorTable;
  static final com.google.protobuf.Descriptors.Descriptor
    internal_static_WISE_FuelProto_IsfO1_Parms_descriptor;
  static final 
    com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
      internal_static_WISE_FuelProto_IsfO1_Parms_fieldAccessorTable;

  public static com.google.protobuf.Descriptors.FileDescriptor
      getDescriptor() {
    return descriptor;
  }
  private static  com.google.protobuf.Descriptors.FileDescriptor
      descriptor;
  static {
    java.lang.String[] descriptorData = {
      "\n\tisf.proto\022\016WISE.FuelProto\032\nmath.proto\032" +
      "\017fuelNames.proto\"\224\001\n\005IsfC1\022\017\n\007version\030\001 " +
      "\001(\005\022+\n\007default\030\002 \001(\0162\030.WISE.FuelProto.Fu" +
      "elNameH\000\022,\n\005parms\030\003 \001(\0132\033.WISE.FuelProto" +
      ".IsfC1.ParmsH\000\032\030\n\005Parms\022\017\n\007version\030\001 \001(\005" +
      "B\005\n\003msg\"\224\001\n\005IsfM1\022\017\n\007version\030\001 \001(\005\022+\n\007de" +
      "fault\030\002 \001(\0162\030.WISE.FuelProto.FuelNameH\000\022" +
      ",\n\005parms\030\003 \001(\0132\033.WISE.FuelProto.IsfM1.Pa" +
      "rmsH\000\032\030\n\005Parms\022\017\n\007version\030\001 \001(\005B\005\n\003msg\"\366" +
      "\001\n\007IsfM3M4\022\017\n\007version\030\001 \001(\005\022+\n\007default\030\002" +
      " \001(\0162\030.WISE.FuelProto.FuelNameH\000\022.\n\005parm" +
      "s\030\003 \001(\0132\035.WISE.FuelProto.IsfM3M4.ParmsH\000" +
      "\032v\n\005Parms\022\017\n\007version\030\001 \001(\005\022\021\n\005notes\030\002 \001(" +
      "\tB\002\030\001\022\027\n\001a\030\003 \001(\0132\014.Math.Double\022\027\n\001b\030\004 \001(" +
      "\0132\014.Math.Double\022\027\n\001c\030\005 \001(\0132\014.Math.Double" +
      "B\005\n\003msg\"\236\002\n\005IsfO1\022\017\n\007version\030\001 \001(\005\022+\n\007de" +
      "fault\030\002 \001(\0162\030.WISE.FuelProto.FuelNameH\000\022" +
      ",\n\005parms\030\003 \001(\0132\033.WISE.FuelProto.IsfO1.Pa" +
      "rmsH\000\032\241\001\n\005Parms\022\017\n\007version\030\001 \001(\005\022\037\n\tthre" +
      "shold\030\002 \001(\0132\014.Math.Double\022\030\n\002f1\030\003 \001(\0132\014." +
      "Math.Double\022\030\n\002f2\030\004 \001(\0132\014.Math.Double\022\030\n" +
      "\002f3\030\005 \001(\0132\014.Math.Double\022\030\n\002f4\030\006 \001(\0132\014.Ma" +
      "th.DoubleB\005\n\003msgB\'\n\022ca.wise.fuel.protoP\001" +
      "\252\002\016WISE.FuelProtob\006proto3"
    };
    descriptor = com.google.protobuf.Descriptors.FileDescriptor
      .internalBuildGeneratedFileFrom(descriptorData,
        new com.google.protobuf.Descriptors.FileDescriptor[] {
          ca.hss.math.proto.Math.getDescriptor(),
          ca.wise.fuel.proto.FuelNames.getDescriptor(),
        });
    internal_static_WISE_FuelProto_IsfC1_descriptor =
      getDescriptor().getMessageTypes().get(0);
    internal_static_WISE_FuelProto_IsfC1_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessageV3.FieldAccessorTable(
        internal_static_WISE_FuelProto_IsfC1_descriptor,
        new java.lang.String[] { "Version", "Default", "Parms", "Msg", });
    internal_static_WISE_FuelProto_IsfC1_Parms_descriptor =
      internal_static_WISE_FuelProto_IsfC1_descriptor.getNestedTypes().get(0);
    internal_static_WISE_FuelProto_IsfC1_Parms_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessageV3.FieldAccessorTable(
        internal_static_WISE_FuelProto_IsfC1_Parms_descriptor,
        new java.lang.String[] { "Version", });
    internal_static_WISE_FuelProto_IsfM1_descriptor =
      getDescriptor().getMessageTypes().get(1);
    internal_static_WISE_FuelProto_IsfM1_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessageV3.FieldAccessorTable(
        internal_static_WISE_FuelProto_IsfM1_descriptor,
        new java.lang.String[] { "Version", "Default", "Parms", "Msg", });
    internal_static_WISE_FuelProto_IsfM1_Parms_descriptor =
      internal_static_WISE_FuelProto_IsfM1_descriptor.getNestedTypes().get(0);
    internal_static_WISE_FuelProto_IsfM1_Parms_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessageV3.FieldAccessorTable(
        internal_static_WISE_FuelProto_IsfM1_Parms_descriptor,
        new java.lang.String[] { "Version", });
    internal_static_WISE_FuelProto_IsfM3M4_descriptor =
      getDescriptor().getMessageTypes().get(2);
    internal_static_WISE_FuelProto_IsfM3M4_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessageV3.FieldAccessorTable(
        internal_static_WISE_FuelProto_IsfM3M4_descriptor,
        new java.lang.String[] { "Version", "Default", "Parms", "Msg", });
    internal_static_WISE_FuelProto_IsfM3M4_Parms_descriptor =
      internal_static_WISE_FuelProto_IsfM3M4_descriptor.getNestedTypes().get(0);
    internal_static_WISE_FuelProto_IsfM3M4_Parms_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessageV3.FieldAccessorTable(
        internal_static_WISE_FuelProto_IsfM3M4_Parms_descriptor,
        new java.lang.String[] { "Version", "Notes", "A", "B", "C", });
    internal_static_WISE_FuelProto_IsfO1_descriptor =
      getDescriptor().getMessageTypes().get(3);
    internal_static_WISE_FuelProto_IsfO1_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessageV3.FieldAccessorTable(
        internal_static_WISE_FuelProto_IsfO1_descriptor,
        new java.lang.String[] { "Version", "Default", "Parms", "Msg", });
    internal_static_WISE_FuelProto_IsfO1_Parms_descriptor =
      internal_static_WISE_FuelProto_IsfO1_descriptor.getNestedTypes().get(0);
    internal_static_WISE_FuelProto_IsfO1_Parms_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessageV3.FieldAccessorTable(
        internal_static_WISE_FuelProto_IsfO1_Parms_descriptor,
        new java.lang.String[] { "Version", "Threshold", "F1", "F2", "F3", "F4", });
    ca.hss.math.proto.Math.getDescriptor();
    ca.wise.fuel.proto.FuelNames.getDescriptor();
  }

  // @@protoc_insertion_point(outer_class_scope)
}
