// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ccwfgmFuel.proto

package ca.wise.fuel.proto;

/**
 * Protobuf type {@code WISE.FuelProto.AccAlphaAttribute}
 */
public final class AccAlphaAttribute extends
    com.google.protobuf.GeneratedMessageV3 implements
    // @@protoc_insertion_point(message_implements:WISE.FuelProto.AccAlphaAttribute)
    AccAlphaAttributeOrBuilder {
private static final long serialVersionUID = 0L;
  // Use AccAlphaAttribute.newBuilder() to construct.
  private AccAlphaAttribute(com.google.protobuf.GeneratedMessageV3.Builder<?> builder) {
    super(builder);
  }
  private AccAlphaAttribute() {
  }

  @java.lang.Override
  @SuppressWarnings({"unused"})
  protected java.lang.Object newInstance(
      UnusedPrivateParameter unused) {
    return new AccAlphaAttribute();
  }

  @java.lang.Override
  public final com.google.protobuf.UnknownFieldSet
  getUnknownFields() {
    return this.unknownFields;
  }
  private AccAlphaAttribute(
      com.google.protobuf.CodedInputStream input,
      com.google.protobuf.ExtensionRegistryLite extensionRegistry)
      throws com.google.protobuf.InvalidProtocolBufferException {
    this();
    if (extensionRegistry == null) {
      throw new java.lang.NullPointerException();
    }
    com.google.protobuf.UnknownFieldSet.Builder unknownFields =
        com.google.protobuf.UnknownFieldSet.newBuilder();
    try {
      boolean done = false;
      while (!done) {
        int tag = input.readTag();
        switch (tag) {
          case 0:
            done = true;
            break;
          case 8: {

            version_ = input.readInt32();
            break;
          }
          case 16: {

            commonField_ = input.readInt64();
            break;
          }
          case 26: {
            ca.wise.fuel.proto.AccAlphaClosed.Builder subBuilder = null;
            if (msgCase_ == 3) {
              subBuilder = ((ca.wise.fuel.proto.AccAlphaClosed) msg_).toBuilder();
            }
            msg_ =
                input.readMessage(ca.wise.fuel.proto.AccAlphaClosed.parser(), extensionRegistry);
            if (subBuilder != null) {
              subBuilder.mergeFrom((ca.wise.fuel.proto.AccAlphaClosed) msg_);
              msg_ = subBuilder.buildPartial();
            }
            msgCase_ = 3;
            break;
          }
          case 34: {
            ca.wise.fuel.proto.AccAlphaOpen.Builder subBuilder = null;
            if (msgCase_ == 4) {
              subBuilder = ((ca.wise.fuel.proto.AccAlphaOpen) msg_).toBuilder();
            }
            msg_ =
                input.readMessage(ca.wise.fuel.proto.AccAlphaOpen.parser(), extensionRegistry);
            if (subBuilder != null) {
              subBuilder.mergeFrom((ca.wise.fuel.proto.AccAlphaOpen) msg_);
              msg_ = subBuilder.buildPartial();
            }
            msgCase_ = 4;
            break;
          }
          default: {
            if (!parseUnknownField(
                input, unknownFields, extensionRegistry, tag)) {
              done = true;
            }
            break;
          }
        }
      }
    } catch (com.google.protobuf.InvalidProtocolBufferException e) {
      throw e.setUnfinishedMessage(this);
    } catch (java.io.IOException e) {
      throw new com.google.protobuf.InvalidProtocolBufferException(
          e).setUnfinishedMessage(this);
    } finally {
      this.unknownFields = unknownFields.build();
      makeExtensionsImmutable();
    }
  }
  public static final com.google.protobuf.Descriptors.Descriptor
      getDescriptor() {
    return ca.wise.fuel.proto.CcwfgmFuelOuterClass.internal_static_WISE_FuelProto_AccAlphaAttribute_descriptor;
  }

  @java.lang.Override
  protected com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
      internalGetFieldAccessorTable() {
    return ca.wise.fuel.proto.CcwfgmFuelOuterClass.internal_static_WISE_FuelProto_AccAlphaAttribute_fieldAccessorTable
        .ensureFieldAccessorsInitialized(
            ca.wise.fuel.proto.AccAlphaAttribute.class, ca.wise.fuel.proto.AccAlphaAttribute.Builder.class);
  }

  private int msgCase_ = 0;
  private java.lang.Object msg_;
  public enum MsgCase
      implements com.google.protobuf.Internal.EnumLite,
          com.google.protobuf.AbstractMessage.InternalOneOfEnum {
    ALPHACLOSED(3),
    ALPHAOPEN(4),
    MSG_NOT_SET(0);
    private final int value;
    private MsgCase(int value) {
      this.value = value;
    }
    /**
     * @param value The number of the enum to look for.
     * @return The enum associated with the given number.
     * @deprecated Use {@link #forNumber(int)} instead.
     */
    @java.lang.Deprecated
    public static MsgCase valueOf(int value) {
      return forNumber(value);
    }

    public static MsgCase forNumber(int value) {
      switch (value) {
        case 3: return ALPHACLOSED;
        case 4: return ALPHAOPEN;
        case 0: return MSG_NOT_SET;
        default: return null;
      }
    }
    public int getNumber() {
      return this.value;
    }
  };

  public MsgCase
  getMsgCase() {
    return MsgCase.forNumber(
        msgCase_);
  }

  public static final int VERSION_FIELD_NUMBER = 1;
  private int version_;
  /**
   * <code>int32 version = 1;</code>
   * @return The version.
   */
  @java.lang.Override
  public int getVersion() {
    return version_;
  }

  public static final int COMMONFIELD_FIELD_NUMBER = 2;
  private long commonField_;
  /**
   * <code>int64 commonField = 2 [deprecated = true];</code>
   * @return The commonField.
   */
  @java.lang.Override
  @java.lang.Deprecated public long getCommonField() {
    return commonField_;
  }

  public static final int ALPHACLOSED_FIELD_NUMBER = 3;
  /**
   * <code>.WISE.FuelProto.AccAlphaClosed alphaClosed = 3;</code>
   * @return Whether the alphaClosed field is set.
   */
  @java.lang.Override
  public boolean hasAlphaClosed() {
    return msgCase_ == 3;
  }
  /**
   * <code>.WISE.FuelProto.AccAlphaClosed alphaClosed = 3;</code>
   * @return The alphaClosed.
   */
  @java.lang.Override
  public ca.wise.fuel.proto.AccAlphaClosed getAlphaClosed() {
    if (msgCase_ == 3) {
       return (ca.wise.fuel.proto.AccAlphaClosed) msg_;
    }
    return ca.wise.fuel.proto.AccAlphaClosed.getDefaultInstance();
  }
  /**
   * <code>.WISE.FuelProto.AccAlphaClosed alphaClosed = 3;</code>
   */
  @java.lang.Override
  public ca.wise.fuel.proto.AccAlphaClosedOrBuilder getAlphaClosedOrBuilder() {
    if (msgCase_ == 3) {
       return (ca.wise.fuel.proto.AccAlphaClosed) msg_;
    }
    return ca.wise.fuel.proto.AccAlphaClosed.getDefaultInstance();
  }

  public static final int ALPHAOPEN_FIELD_NUMBER = 4;
  /**
   * <code>.WISE.FuelProto.AccAlphaOpen alphaOpen = 4;</code>
   * @return Whether the alphaOpen field is set.
   */
  @java.lang.Override
  public boolean hasAlphaOpen() {
    return msgCase_ == 4;
  }
  /**
   * <code>.WISE.FuelProto.AccAlphaOpen alphaOpen = 4;</code>
   * @return The alphaOpen.
   */
  @java.lang.Override
  public ca.wise.fuel.proto.AccAlphaOpen getAlphaOpen() {
    if (msgCase_ == 4) {
       return (ca.wise.fuel.proto.AccAlphaOpen) msg_;
    }
    return ca.wise.fuel.proto.AccAlphaOpen.getDefaultInstance();
  }
  /**
   * <code>.WISE.FuelProto.AccAlphaOpen alphaOpen = 4;</code>
   */
  @java.lang.Override
  public ca.wise.fuel.proto.AccAlphaOpenOrBuilder getAlphaOpenOrBuilder() {
    if (msgCase_ == 4) {
       return (ca.wise.fuel.proto.AccAlphaOpen) msg_;
    }
    return ca.wise.fuel.proto.AccAlphaOpen.getDefaultInstance();
  }

  private byte memoizedIsInitialized = -1;
  @java.lang.Override
  public final boolean isInitialized() {
    byte isInitialized = memoizedIsInitialized;
    if (isInitialized == 1) return true;
    if (isInitialized == 0) return false;

    memoizedIsInitialized = 1;
    return true;
  }

  @java.lang.Override
  public void writeTo(com.google.protobuf.CodedOutputStream output)
                      throws java.io.IOException {
    if (version_ != 0) {
      output.writeInt32(1, version_);
    }
    if (commonField_ != 0L) {
      output.writeInt64(2, commonField_);
    }
    if (msgCase_ == 3) {
      output.writeMessage(3, (ca.wise.fuel.proto.AccAlphaClosed) msg_);
    }
    if (msgCase_ == 4) {
      output.writeMessage(4, (ca.wise.fuel.proto.AccAlphaOpen) msg_);
    }
    unknownFields.writeTo(output);
  }

  @java.lang.Override
  public int getSerializedSize() {
    int size = memoizedSize;
    if (size != -1) return size;

    size = 0;
    if (version_ != 0) {
      size += com.google.protobuf.CodedOutputStream
        .computeInt32Size(1, version_);
    }
    if (commonField_ != 0L) {
      size += com.google.protobuf.CodedOutputStream
        .computeInt64Size(2, commonField_);
    }
    if (msgCase_ == 3) {
      size += com.google.protobuf.CodedOutputStream
        .computeMessageSize(3, (ca.wise.fuel.proto.AccAlphaClosed) msg_);
    }
    if (msgCase_ == 4) {
      size += com.google.protobuf.CodedOutputStream
        .computeMessageSize(4, (ca.wise.fuel.proto.AccAlphaOpen) msg_);
    }
    size += unknownFields.getSerializedSize();
    memoizedSize = size;
    return size;
  }

  @java.lang.Override
  public boolean equals(final java.lang.Object obj) {
    if (obj == this) {
     return true;
    }
    if (!(obj instanceof ca.wise.fuel.proto.AccAlphaAttribute)) {
      return super.equals(obj);
    }
    ca.wise.fuel.proto.AccAlphaAttribute other = (ca.wise.fuel.proto.AccAlphaAttribute) obj;

    if (getVersion()
        != other.getVersion()) return false;
    if (getCommonField()
        != other.getCommonField()) return false;
    if (!getMsgCase().equals(other.getMsgCase())) return false;
    switch (msgCase_) {
      case 3:
        if (!getAlphaClosed()
            .equals(other.getAlphaClosed())) return false;
        break;
      case 4:
        if (!getAlphaOpen()
            .equals(other.getAlphaOpen())) return false;
        break;
      case 0:
      default:
    }
    if (!unknownFields.equals(other.unknownFields)) return false;
    return true;
  }

  @java.lang.Override
  public int hashCode() {
    if (memoizedHashCode != 0) {
      return memoizedHashCode;
    }
    int hash = 41;
    hash = (19 * hash) + getDescriptor().hashCode();
    hash = (37 * hash) + VERSION_FIELD_NUMBER;
    hash = (53 * hash) + getVersion();
    hash = (37 * hash) + COMMONFIELD_FIELD_NUMBER;
    hash = (53 * hash) + com.google.protobuf.Internal.hashLong(
        getCommonField());
    switch (msgCase_) {
      case 3:
        hash = (37 * hash) + ALPHACLOSED_FIELD_NUMBER;
        hash = (53 * hash) + getAlphaClosed().hashCode();
        break;
      case 4:
        hash = (37 * hash) + ALPHAOPEN_FIELD_NUMBER;
        hash = (53 * hash) + getAlphaOpen().hashCode();
        break;
      case 0:
      default:
    }
    hash = (29 * hash) + unknownFields.hashCode();
    memoizedHashCode = hash;
    return hash;
  }

  public static ca.wise.fuel.proto.AccAlphaAttribute parseFrom(
      java.nio.ByteBuffer data)
      throws com.google.protobuf.InvalidProtocolBufferException {
    return PARSER.parseFrom(data);
  }
  public static ca.wise.fuel.proto.AccAlphaAttribute parseFrom(
      java.nio.ByteBuffer data,
      com.google.protobuf.ExtensionRegistryLite extensionRegistry)
      throws com.google.protobuf.InvalidProtocolBufferException {
    return PARSER.parseFrom(data, extensionRegistry);
  }
  public static ca.wise.fuel.proto.AccAlphaAttribute parseFrom(
      com.google.protobuf.ByteString data)
      throws com.google.protobuf.InvalidProtocolBufferException {
    return PARSER.parseFrom(data);
  }
  public static ca.wise.fuel.proto.AccAlphaAttribute parseFrom(
      com.google.protobuf.ByteString data,
      com.google.protobuf.ExtensionRegistryLite extensionRegistry)
      throws com.google.protobuf.InvalidProtocolBufferException {
    return PARSER.parseFrom(data, extensionRegistry);
  }
  public static ca.wise.fuel.proto.AccAlphaAttribute parseFrom(byte[] data)
      throws com.google.protobuf.InvalidProtocolBufferException {
    return PARSER.parseFrom(data);
  }
  public static ca.wise.fuel.proto.AccAlphaAttribute parseFrom(
      byte[] data,
      com.google.protobuf.ExtensionRegistryLite extensionRegistry)
      throws com.google.protobuf.InvalidProtocolBufferException {
    return PARSER.parseFrom(data, extensionRegistry);
  }
  public static ca.wise.fuel.proto.AccAlphaAttribute parseFrom(java.io.InputStream input)
      throws java.io.IOException {
    return com.google.protobuf.GeneratedMessageV3
        .parseWithIOException(PARSER, input);
  }
  public static ca.wise.fuel.proto.AccAlphaAttribute parseFrom(
      java.io.InputStream input,
      com.google.protobuf.ExtensionRegistryLite extensionRegistry)
      throws java.io.IOException {
    return com.google.protobuf.GeneratedMessageV3
        .parseWithIOException(PARSER, input, extensionRegistry);
  }
  public static ca.wise.fuel.proto.AccAlphaAttribute parseDelimitedFrom(java.io.InputStream input)
      throws java.io.IOException {
    return com.google.protobuf.GeneratedMessageV3
        .parseDelimitedWithIOException(PARSER, input);
  }
  public static ca.wise.fuel.proto.AccAlphaAttribute parseDelimitedFrom(
      java.io.InputStream input,
      com.google.protobuf.ExtensionRegistryLite extensionRegistry)
      throws java.io.IOException {
    return com.google.protobuf.GeneratedMessageV3
        .parseDelimitedWithIOException(PARSER, input, extensionRegistry);
  }
  public static ca.wise.fuel.proto.AccAlphaAttribute parseFrom(
      com.google.protobuf.CodedInputStream input)
      throws java.io.IOException {
    return com.google.protobuf.GeneratedMessageV3
        .parseWithIOException(PARSER, input);
  }
  public static ca.wise.fuel.proto.AccAlphaAttribute parseFrom(
      com.google.protobuf.CodedInputStream input,
      com.google.protobuf.ExtensionRegistryLite extensionRegistry)
      throws java.io.IOException {
    return com.google.protobuf.GeneratedMessageV3
        .parseWithIOException(PARSER, input, extensionRegistry);
  }

  @java.lang.Override
  public Builder newBuilderForType() { return newBuilder(); }
  public static Builder newBuilder() {
    return DEFAULT_INSTANCE.toBuilder();
  }
  public static Builder newBuilder(ca.wise.fuel.proto.AccAlphaAttribute prototype) {
    return DEFAULT_INSTANCE.toBuilder().mergeFrom(prototype);
  }
  @java.lang.Override
  public Builder toBuilder() {
    return this == DEFAULT_INSTANCE
        ? new Builder() : new Builder().mergeFrom(this);
  }

  @java.lang.Override
  protected Builder newBuilderForType(
      com.google.protobuf.GeneratedMessageV3.BuilderParent parent) {
    Builder builder = new Builder(parent);
    return builder;
  }
  /**
   * Protobuf type {@code WISE.FuelProto.AccAlphaAttribute}
   */
  public static final class Builder extends
      com.google.protobuf.GeneratedMessageV3.Builder<Builder> implements
      // @@protoc_insertion_point(builder_implements:WISE.FuelProto.AccAlphaAttribute)
      ca.wise.fuel.proto.AccAlphaAttributeOrBuilder {
    public static final com.google.protobuf.Descriptors.Descriptor
        getDescriptor() {
      return ca.wise.fuel.proto.CcwfgmFuelOuterClass.internal_static_WISE_FuelProto_AccAlphaAttribute_descriptor;
    }

    @java.lang.Override
    protected com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
        internalGetFieldAccessorTable() {
      return ca.wise.fuel.proto.CcwfgmFuelOuterClass.internal_static_WISE_FuelProto_AccAlphaAttribute_fieldAccessorTable
          .ensureFieldAccessorsInitialized(
              ca.wise.fuel.proto.AccAlphaAttribute.class, ca.wise.fuel.proto.AccAlphaAttribute.Builder.class);
    }

    // Construct using ca.wise.fuel.proto.AccAlphaAttribute.newBuilder()
    private Builder() {
      maybeForceBuilderInitialization();
    }

    private Builder(
        com.google.protobuf.GeneratedMessageV3.BuilderParent parent) {
      super(parent);
      maybeForceBuilderInitialization();
    }
    private void maybeForceBuilderInitialization() {
      if (com.google.protobuf.GeneratedMessageV3
              .alwaysUseFieldBuilders) {
      }
    }
    @java.lang.Override
    public Builder clear() {
      super.clear();
      version_ = 0;

      commonField_ = 0L;

      msgCase_ = 0;
      msg_ = null;
      return this;
    }

    @java.lang.Override
    public com.google.protobuf.Descriptors.Descriptor
        getDescriptorForType() {
      return ca.wise.fuel.proto.CcwfgmFuelOuterClass.internal_static_WISE_FuelProto_AccAlphaAttribute_descriptor;
    }

    @java.lang.Override
    public ca.wise.fuel.proto.AccAlphaAttribute getDefaultInstanceForType() {
      return ca.wise.fuel.proto.AccAlphaAttribute.getDefaultInstance();
    }

    @java.lang.Override
    public ca.wise.fuel.proto.AccAlphaAttribute build() {
      ca.wise.fuel.proto.AccAlphaAttribute result = buildPartial();
      if (!result.isInitialized()) {
        throw newUninitializedMessageException(result);
      }
      return result;
    }

    @java.lang.Override
    public ca.wise.fuel.proto.AccAlphaAttribute buildPartial() {
      ca.wise.fuel.proto.AccAlphaAttribute result = new ca.wise.fuel.proto.AccAlphaAttribute(this);
      result.version_ = version_;
      result.commonField_ = commonField_;
      if (msgCase_ == 3) {
        if (alphaClosedBuilder_ == null) {
          result.msg_ = msg_;
        } else {
          result.msg_ = alphaClosedBuilder_.build();
        }
      }
      if (msgCase_ == 4) {
        if (alphaOpenBuilder_ == null) {
          result.msg_ = msg_;
        } else {
          result.msg_ = alphaOpenBuilder_.build();
        }
      }
      result.msgCase_ = msgCase_;
      onBuilt();
      return result;
    }

    @java.lang.Override
    public Builder clone() {
      return super.clone();
    }
    @java.lang.Override
    public Builder setField(
        com.google.protobuf.Descriptors.FieldDescriptor field,
        java.lang.Object value) {
      return super.setField(field, value);
    }
    @java.lang.Override
    public Builder clearField(
        com.google.protobuf.Descriptors.FieldDescriptor field) {
      return super.clearField(field);
    }
    @java.lang.Override
    public Builder clearOneof(
        com.google.protobuf.Descriptors.OneofDescriptor oneof) {
      return super.clearOneof(oneof);
    }
    @java.lang.Override
    public Builder setRepeatedField(
        com.google.protobuf.Descriptors.FieldDescriptor field,
        int index, java.lang.Object value) {
      return super.setRepeatedField(field, index, value);
    }
    @java.lang.Override
    public Builder addRepeatedField(
        com.google.protobuf.Descriptors.FieldDescriptor field,
        java.lang.Object value) {
      return super.addRepeatedField(field, value);
    }
    @java.lang.Override
    public Builder mergeFrom(com.google.protobuf.Message other) {
      if (other instanceof ca.wise.fuel.proto.AccAlphaAttribute) {
        return mergeFrom((ca.wise.fuel.proto.AccAlphaAttribute)other);
      } else {
        super.mergeFrom(other);
        return this;
      }
    }

    public Builder mergeFrom(ca.wise.fuel.proto.AccAlphaAttribute other) {
      if (other == ca.wise.fuel.proto.AccAlphaAttribute.getDefaultInstance()) return this;
      if (other.getVersion() != 0) {
        setVersion(other.getVersion());
      }
      if (other.getCommonField() != 0L) {
        setCommonField(other.getCommonField());
      }
      switch (other.getMsgCase()) {
        case ALPHACLOSED: {
          mergeAlphaClosed(other.getAlphaClosed());
          break;
        }
        case ALPHAOPEN: {
          mergeAlphaOpen(other.getAlphaOpen());
          break;
        }
        case MSG_NOT_SET: {
          break;
        }
      }
      this.mergeUnknownFields(other.unknownFields);
      onChanged();
      return this;
    }

    @java.lang.Override
    public final boolean isInitialized() {
      return true;
    }

    @java.lang.Override
    public Builder mergeFrom(
        com.google.protobuf.CodedInputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      ca.wise.fuel.proto.AccAlphaAttribute parsedMessage = null;
      try {
        parsedMessage = PARSER.parsePartialFrom(input, extensionRegistry);
      } catch (com.google.protobuf.InvalidProtocolBufferException e) {
        parsedMessage = (ca.wise.fuel.proto.AccAlphaAttribute) e.getUnfinishedMessage();
        throw e.unwrapIOException();
      } finally {
        if (parsedMessage != null) {
          mergeFrom(parsedMessage);
        }
      }
      return this;
    }
    private int msgCase_ = 0;
    private java.lang.Object msg_;
    public MsgCase
        getMsgCase() {
      return MsgCase.forNumber(
          msgCase_);
    }

    public Builder clearMsg() {
      msgCase_ = 0;
      msg_ = null;
      onChanged();
      return this;
    }


    private int version_ ;
    /**
     * <code>int32 version = 1;</code>
     * @return The version.
     */
    @java.lang.Override
    public int getVersion() {
      return version_;
    }
    /**
     * <code>int32 version = 1;</code>
     * @param value The version to set.
     * @return This builder for chaining.
     */
    public Builder setVersion(int value) {
      
      version_ = value;
      onChanged();
      return this;
    }
    /**
     * <code>int32 version = 1;</code>
     * @return This builder for chaining.
     */
    public Builder clearVersion() {
      
      version_ = 0;
      onChanged();
      return this;
    }

    private long commonField_ ;
    /**
     * <code>int64 commonField = 2 [deprecated = true];</code>
     * @return The commonField.
     */
    @java.lang.Override
    @java.lang.Deprecated public long getCommonField() {
      return commonField_;
    }
    /**
     * <code>int64 commonField = 2 [deprecated = true];</code>
     * @param value The commonField to set.
     * @return This builder for chaining.
     */
    @java.lang.Deprecated public Builder setCommonField(long value) {
      
      commonField_ = value;
      onChanged();
      return this;
    }
    /**
     * <code>int64 commonField = 2 [deprecated = true];</code>
     * @return This builder for chaining.
     */
    @java.lang.Deprecated public Builder clearCommonField() {
      
      commonField_ = 0L;
      onChanged();
      return this;
    }

    private com.google.protobuf.SingleFieldBuilderV3<
        ca.wise.fuel.proto.AccAlphaClosed, ca.wise.fuel.proto.AccAlphaClosed.Builder, ca.wise.fuel.proto.AccAlphaClosedOrBuilder> alphaClosedBuilder_;
    /**
     * <code>.WISE.FuelProto.AccAlphaClosed alphaClosed = 3;</code>
     * @return Whether the alphaClosed field is set.
     */
    @java.lang.Override
    public boolean hasAlphaClosed() {
      return msgCase_ == 3;
    }
    /**
     * <code>.WISE.FuelProto.AccAlphaClosed alphaClosed = 3;</code>
     * @return The alphaClosed.
     */
    @java.lang.Override
    public ca.wise.fuel.proto.AccAlphaClosed getAlphaClosed() {
      if (alphaClosedBuilder_ == null) {
        if (msgCase_ == 3) {
          return (ca.wise.fuel.proto.AccAlphaClosed) msg_;
        }
        return ca.wise.fuel.proto.AccAlphaClosed.getDefaultInstance();
      } else {
        if (msgCase_ == 3) {
          return alphaClosedBuilder_.getMessage();
        }
        return ca.wise.fuel.proto.AccAlphaClosed.getDefaultInstance();
      }
    }
    /**
     * <code>.WISE.FuelProto.AccAlphaClosed alphaClosed = 3;</code>
     */
    public Builder setAlphaClosed(ca.wise.fuel.proto.AccAlphaClosed value) {
      if (alphaClosedBuilder_ == null) {
        if (value == null) {
          throw new NullPointerException();
        }
        msg_ = value;
        onChanged();
      } else {
        alphaClosedBuilder_.setMessage(value);
      }
      msgCase_ = 3;
      return this;
    }
    /**
     * <code>.WISE.FuelProto.AccAlphaClosed alphaClosed = 3;</code>
     */
    public Builder setAlphaClosed(
        ca.wise.fuel.proto.AccAlphaClosed.Builder builderForValue) {
      if (alphaClosedBuilder_ == null) {
        msg_ = builderForValue.build();
        onChanged();
      } else {
        alphaClosedBuilder_.setMessage(builderForValue.build());
      }
      msgCase_ = 3;
      return this;
    }
    /**
     * <code>.WISE.FuelProto.AccAlphaClosed alphaClosed = 3;</code>
     */
    public Builder mergeAlphaClosed(ca.wise.fuel.proto.AccAlphaClosed value) {
      if (alphaClosedBuilder_ == null) {
        if (msgCase_ == 3 &&
            msg_ != ca.wise.fuel.proto.AccAlphaClosed.getDefaultInstance()) {
          msg_ = ca.wise.fuel.proto.AccAlphaClosed.newBuilder((ca.wise.fuel.proto.AccAlphaClosed) msg_)
              .mergeFrom(value).buildPartial();
        } else {
          msg_ = value;
        }
        onChanged();
      } else {
        if (msgCase_ == 3) {
          alphaClosedBuilder_.mergeFrom(value);
        }
        alphaClosedBuilder_.setMessage(value);
      }
      msgCase_ = 3;
      return this;
    }
    /**
     * <code>.WISE.FuelProto.AccAlphaClosed alphaClosed = 3;</code>
     */
    public Builder clearAlphaClosed() {
      if (alphaClosedBuilder_ == null) {
        if (msgCase_ == 3) {
          msgCase_ = 0;
          msg_ = null;
          onChanged();
        }
      } else {
        if (msgCase_ == 3) {
          msgCase_ = 0;
          msg_ = null;
        }
        alphaClosedBuilder_.clear();
      }
      return this;
    }
    /**
     * <code>.WISE.FuelProto.AccAlphaClosed alphaClosed = 3;</code>
     */
    public ca.wise.fuel.proto.AccAlphaClosed.Builder getAlphaClosedBuilder() {
      return getAlphaClosedFieldBuilder().getBuilder();
    }
    /**
     * <code>.WISE.FuelProto.AccAlphaClosed alphaClosed = 3;</code>
     */
    @java.lang.Override
    public ca.wise.fuel.proto.AccAlphaClosedOrBuilder getAlphaClosedOrBuilder() {
      if ((msgCase_ == 3) && (alphaClosedBuilder_ != null)) {
        return alphaClosedBuilder_.getMessageOrBuilder();
      } else {
        if (msgCase_ == 3) {
          return (ca.wise.fuel.proto.AccAlphaClosed) msg_;
        }
        return ca.wise.fuel.proto.AccAlphaClosed.getDefaultInstance();
      }
    }
    /**
     * <code>.WISE.FuelProto.AccAlphaClosed alphaClosed = 3;</code>
     */
    private com.google.protobuf.SingleFieldBuilderV3<
        ca.wise.fuel.proto.AccAlphaClosed, ca.wise.fuel.proto.AccAlphaClosed.Builder, ca.wise.fuel.proto.AccAlphaClosedOrBuilder> 
        getAlphaClosedFieldBuilder() {
      if (alphaClosedBuilder_ == null) {
        if (!(msgCase_ == 3)) {
          msg_ = ca.wise.fuel.proto.AccAlphaClosed.getDefaultInstance();
        }
        alphaClosedBuilder_ = new com.google.protobuf.SingleFieldBuilderV3<
            ca.wise.fuel.proto.AccAlphaClosed, ca.wise.fuel.proto.AccAlphaClosed.Builder, ca.wise.fuel.proto.AccAlphaClosedOrBuilder>(
                (ca.wise.fuel.proto.AccAlphaClosed) msg_,
                getParentForChildren(),
                isClean());
        msg_ = null;
      }
      msgCase_ = 3;
      onChanged();;
      return alphaClosedBuilder_;
    }

    private com.google.protobuf.SingleFieldBuilderV3<
        ca.wise.fuel.proto.AccAlphaOpen, ca.wise.fuel.proto.AccAlphaOpen.Builder, ca.wise.fuel.proto.AccAlphaOpenOrBuilder> alphaOpenBuilder_;
    /**
     * <code>.WISE.FuelProto.AccAlphaOpen alphaOpen = 4;</code>
     * @return Whether the alphaOpen field is set.
     */
    @java.lang.Override
    public boolean hasAlphaOpen() {
      return msgCase_ == 4;
    }
    /**
     * <code>.WISE.FuelProto.AccAlphaOpen alphaOpen = 4;</code>
     * @return The alphaOpen.
     */
    @java.lang.Override
    public ca.wise.fuel.proto.AccAlphaOpen getAlphaOpen() {
      if (alphaOpenBuilder_ == null) {
        if (msgCase_ == 4) {
          return (ca.wise.fuel.proto.AccAlphaOpen) msg_;
        }
        return ca.wise.fuel.proto.AccAlphaOpen.getDefaultInstance();
      } else {
        if (msgCase_ == 4) {
          return alphaOpenBuilder_.getMessage();
        }
        return ca.wise.fuel.proto.AccAlphaOpen.getDefaultInstance();
      }
    }
    /**
     * <code>.WISE.FuelProto.AccAlphaOpen alphaOpen = 4;</code>
     */
    public Builder setAlphaOpen(ca.wise.fuel.proto.AccAlphaOpen value) {
      if (alphaOpenBuilder_ == null) {
        if (value == null) {
          throw new NullPointerException();
        }
        msg_ = value;
        onChanged();
      } else {
        alphaOpenBuilder_.setMessage(value);
      }
      msgCase_ = 4;
      return this;
    }
    /**
     * <code>.WISE.FuelProto.AccAlphaOpen alphaOpen = 4;</code>
     */
    public Builder setAlphaOpen(
        ca.wise.fuel.proto.AccAlphaOpen.Builder builderForValue) {
      if (alphaOpenBuilder_ == null) {
        msg_ = builderForValue.build();
        onChanged();
      } else {
        alphaOpenBuilder_.setMessage(builderForValue.build());
      }
      msgCase_ = 4;
      return this;
    }
    /**
     * <code>.WISE.FuelProto.AccAlphaOpen alphaOpen = 4;</code>
     */
    public Builder mergeAlphaOpen(ca.wise.fuel.proto.AccAlphaOpen value) {
      if (alphaOpenBuilder_ == null) {
        if (msgCase_ == 4 &&
            msg_ != ca.wise.fuel.proto.AccAlphaOpen.getDefaultInstance()) {
          msg_ = ca.wise.fuel.proto.AccAlphaOpen.newBuilder((ca.wise.fuel.proto.AccAlphaOpen) msg_)
              .mergeFrom(value).buildPartial();
        } else {
          msg_ = value;
        }
        onChanged();
      } else {
        if (msgCase_ == 4) {
          alphaOpenBuilder_.mergeFrom(value);
        }
        alphaOpenBuilder_.setMessage(value);
      }
      msgCase_ = 4;
      return this;
    }
    /**
     * <code>.WISE.FuelProto.AccAlphaOpen alphaOpen = 4;</code>
     */
    public Builder clearAlphaOpen() {
      if (alphaOpenBuilder_ == null) {
        if (msgCase_ == 4) {
          msgCase_ = 0;
          msg_ = null;
          onChanged();
        }
      } else {
        if (msgCase_ == 4) {
          msgCase_ = 0;
          msg_ = null;
        }
        alphaOpenBuilder_.clear();
      }
      return this;
    }
    /**
     * <code>.WISE.FuelProto.AccAlphaOpen alphaOpen = 4;</code>
     */
    public ca.wise.fuel.proto.AccAlphaOpen.Builder getAlphaOpenBuilder() {
      return getAlphaOpenFieldBuilder().getBuilder();
    }
    /**
     * <code>.WISE.FuelProto.AccAlphaOpen alphaOpen = 4;</code>
     */
    @java.lang.Override
    public ca.wise.fuel.proto.AccAlphaOpenOrBuilder getAlphaOpenOrBuilder() {
      if ((msgCase_ == 4) && (alphaOpenBuilder_ != null)) {
        return alphaOpenBuilder_.getMessageOrBuilder();
      } else {
        if (msgCase_ == 4) {
          return (ca.wise.fuel.proto.AccAlphaOpen) msg_;
        }
        return ca.wise.fuel.proto.AccAlphaOpen.getDefaultInstance();
      }
    }
    /**
     * <code>.WISE.FuelProto.AccAlphaOpen alphaOpen = 4;</code>
     */
    private com.google.protobuf.SingleFieldBuilderV3<
        ca.wise.fuel.proto.AccAlphaOpen, ca.wise.fuel.proto.AccAlphaOpen.Builder, ca.wise.fuel.proto.AccAlphaOpenOrBuilder> 
        getAlphaOpenFieldBuilder() {
      if (alphaOpenBuilder_ == null) {
        if (!(msgCase_ == 4)) {
          msg_ = ca.wise.fuel.proto.AccAlphaOpen.getDefaultInstance();
        }
        alphaOpenBuilder_ = new com.google.protobuf.SingleFieldBuilderV3<
            ca.wise.fuel.proto.AccAlphaOpen, ca.wise.fuel.proto.AccAlphaOpen.Builder, ca.wise.fuel.proto.AccAlphaOpenOrBuilder>(
                (ca.wise.fuel.proto.AccAlphaOpen) msg_,
                getParentForChildren(),
                isClean());
        msg_ = null;
      }
      msgCase_ = 4;
      onChanged();;
      return alphaOpenBuilder_;
    }
    @java.lang.Override
    public final Builder setUnknownFields(
        final com.google.protobuf.UnknownFieldSet unknownFields) {
      return super.setUnknownFields(unknownFields);
    }

    @java.lang.Override
    public final Builder mergeUnknownFields(
        final com.google.protobuf.UnknownFieldSet unknownFields) {
      return super.mergeUnknownFields(unknownFields);
    }


    // @@protoc_insertion_point(builder_scope:WISE.FuelProto.AccAlphaAttribute)
  }

  // @@protoc_insertion_point(class_scope:WISE.FuelProto.AccAlphaAttribute)
  private static final ca.wise.fuel.proto.AccAlphaAttribute DEFAULT_INSTANCE;
  static {
    DEFAULT_INSTANCE = new ca.wise.fuel.proto.AccAlphaAttribute();
  }

  public static ca.wise.fuel.proto.AccAlphaAttribute getDefaultInstance() {
    return DEFAULT_INSTANCE;
  }

  private static final com.google.protobuf.Parser<AccAlphaAttribute>
      PARSER = new com.google.protobuf.AbstractParser<AccAlphaAttribute>() {
    @java.lang.Override
    public AccAlphaAttribute parsePartialFrom(
        com.google.protobuf.CodedInputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return new AccAlphaAttribute(input, extensionRegistry);
    }
  };

  public static com.google.protobuf.Parser<AccAlphaAttribute> parser() {
    return PARSER;
  }

  @java.lang.Override
  public com.google.protobuf.Parser<AccAlphaAttribute> getParserForType() {
    return PARSER;
  }

  @java.lang.Override
  public ca.wise.fuel.proto.AccAlphaAttribute getDefaultInstanceForType() {
    return DEFAULT_INSTANCE;
  }

}

