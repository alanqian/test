/**
 * Autogenerated by Thrift Compiler (0.8.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
package com.avos.recommendation.service;

import org.apache.thrift.scheme.IScheme;
import org.apache.thrift.scheme.SchemeFactory;
import org.apache.thrift.scheme.StandardScheme;

import org.apache.thrift.scheme.TupleScheme;
import org.apache.thrift.protocol.TTupleProtocol;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.EnumMap;
import java.util.Set;
import java.util.HashSet;
import java.util.EnumSet;
import java.util.Collections;
import java.util.BitSet;
import java.nio.ByteBuffer;
import java.util.Arrays;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class RecommendItem implements org.apache.thrift.TBase<RecommendItem, RecommendItem._Fields>, java.io.Serializable, Cloneable {
  private static final org.apache.thrift.protocol.TStruct STRUCT_DESC = new org.apache.thrift.protocol.TStruct("RecommendItem");

  private static final org.apache.thrift.protocol.TField ID_FIELD_DESC = new org.apache.thrift.protocol.TField("id", org.apache.thrift.protocol.TType.STRING, (short)1);
  private static final org.apache.thrift.protocol.TField SCORE_FIELD_DESC = new org.apache.thrift.protocol.TField("score", org.apache.thrift.protocol.TType.DOUBLE, (short)2);
  private static final org.apache.thrift.protocol.TField PROVIDER_FIELD_DESC = new org.apache.thrift.protocol.TField("provider", org.apache.thrift.protocol.TType.STRING, (short)3);
  private static final org.apache.thrift.protocol.TField DETAIL_FIELD_DESC = new org.apache.thrift.protocol.TField("detail", org.apache.thrift.protocol.TType.MAP, (short)4);

  private static final Map<Class<? extends IScheme>, SchemeFactory> schemes = new HashMap<Class<? extends IScheme>, SchemeFactory>();
  static {
    schemes.put(StandardScheme.class, new RecommendItemStandardSchemeFactory());
    schemes.put(TupleScheme.class, new RecommendItemTupleSchemeFactory());
  }

  public String id; // required
  public double score; // required
  public String provider; // required
  public Map<String,String> detail; // required

  /** The set of fields this struct contains, along with convenience methods for finding and manipulating them. */
  public enum _Fields implements org.apache.thrift.TFieldIdEnum {
    ID((short)1, "id"),
    SCORE((short)2, "score"),
    PROVIDER((short)3, "provider"),
    DETAIL((short)4, "detail");

    private static final Map<String, _Fields> byName = new HashMap<String, _Fields>();

    static {
      for (_Fields field : EnumSet.allOf(_Fields.class)) {
        byName.put(field.getFieldName(), field);
      }
    }

    /**
     * Find the _Fields constant that matches fieldId, or null if its not found.
     */
    public static _Fields findByThriftId(int fieldId) {
      switch(fieldId) {
        case 1: // ID
          return ID;
        case 2: // SCORE
          return SCORE;
        case 3: // PROVIDER
          return PROVIDER;
        case 4: // DETAIL
          return DETAIL;
        default:
          return null;
      }
    }

    /**
     * Find the _Fields constant that matches fieldId, throwing an exception
     * if it is not found.
     */
    public static _Fields findByThriftIdOrThrow(int fieldId) {
      _Fields fields = findByThriftId(fieldId);
      if (fields == null) throw new IllegalArgumentException("Field " + fieldId + " doesn't exist!");
      return fields;
    }

    /**
     * Find the _Fields constant that matches name, or null if its not found.
     */
    public static _Fields findByName(String name) {
      return byName.get(name);
    }

    private final short _thriftId;
    private final String _fieldName;

    _Fields(short thriftId, String fieldName) {
      _thriftId = thriftId;
      _fieldName = fieldName;
    }

    public short getThriftFieldId() {
      return _thriftId;
    }

    public String getFieldName() {
      return _fieldName;
    }
  }

  // isset id assignments
  private static final int __SCORE_ISSET_ID = 0;
  private BitSet __isset_bit_vector = new BitSet(1);
  public static final Map<_Fields, org.apache.thrift.meta_data.FieldMetaData> metaDataMap;
  static {
    Map<_Fields, org.apache.thrift.meta_data.FieldMetaData> tmpMap = new EnumMap<_Fields, org.apache.thrift.meta_data.FieldMetaData>(_Fields.class);
    tmpMap.put(_Fields.ID, new org.apache.thrift.meta_data.FieldMetaData("id", org.apache.thrift.TFieldRequirementType.DEFAULT, 
        new org.apache.thrift.meta_data.FieldValueMetaData(org.apache.thrift.protocol.TType.STRING)));
    tmpMap.put(_Fields.SCORE, new org.apache.thrift.meta_data.FieldMetaData("score", org.apache.thrift.TFieldRequirementType.DEFAULT, 
        new org.apache.thrift.meta_data.FieldValueMetaData(org.apache.thrift.protocol.TType.DOUBLE)));
    tmpMap.put(_Fields.PROVIDER, new org.apache.thrift.meta_data.FieldMetaData("provider", org.apache.thrift.TFieldRequirementType.DEFAULT, 
        new org.apache.thrift.meta_data.FieldValueMetaData(org.apache.thrift.protocol.TType.STRING)));
    tmpMap.put(_Fields.DETAIL, new org.apache.thrift.meta_data.FieldMetaData("detail", org.apache.thrift.TFieldRequirementType.DEFAULT, 
        new org.apache.thrift.meta_data.MapMetaData(org.apache.thrift.protocol.TType.MAP, 
            new org.apache.thrift.meta_data.FieldValueMetaData(org.apache.thrift.protocol.TType.STRING), 
            new org.apache.thrift.meta_data.FieldValueMetaData(org.apache.thrift.protocol.TType.STRING))));
    metaDataMap = Collections.unmodifiableMap(tmpMap);
    org.apache.thrift.meta_data.FieldMetaData.addStructMetaDataMap(RecommendItem.class, metaDataMap);
  }

  public RecommendItem() {
  }

  public RecommendItem(
    String id,
    double score,
    String provider,
    Map<String,String> detail)
  {
    this();
    this.id = id;
    this.score = score;
    setScoreIsSet(true);
    this.provider = provider;
    this.detail = detail;
  }

  /**
   * Performs a deep copy on <i>other</i>.
   */
  public RecommendItem(RecommendItem other) {
    __isset_bit_vector.clear();
    __isset_bit_vector.or(other.__isset_bit_vector);
    if (other.isSetId()) {
      this.id = other.id;
    }
    this.score = other.score;
    if (other.isSetProvider()) {
      this.provider = other.provider;
    }
    if (other.isSetDetail()) {
      Map<String,String> __this__detail = new HashMap<String,String>();
      for (Map.Entry<String, String> other_element : other.detail.entrySet()) {

        String other_element_key = other_element.getKey();
        String other_element_value = other_element.getValue();

        String __this__detail_copy_key = other_element_key;

        String __this__detail_copy_value = other_element_value;

        __this__detail.put(__this__detail_copy_key, __this__detail_copy_value);
      }
      this.detail = __this__detail;
    }
  }

  public RecommendItem deepCopy() {
    return new RecommendItem(this);
  }

  @Override
  public void clear() {
    this.id = null;
    setScoreIsSet(false);
    this.score = 0.0;
    this.provider = null;
    this.detail = null;
  }

  public String getId() {
    return this.id;
  }

  public RecommendItem setId(String id) {
    this.id = id;
    return this;
  }

  public void unsetId() {
    this.id = null;
  }

  /** Returns true if field id is set (has been assigned a value) and false otherwise */
  public boolean isSetId() {
    return this.id != null;
  }

  public void setIdIsSet(boolean value) {
    if (!value) {
      this.id = null;
    }
  }

  public double getScore() {
    return this.score;
  }

  public RecommendItem setScore(double score) {
    this.score = score;
    setScoreIsSet(true);
    return this;
  }

  public void unsetScore() {
    __isset_bit_vector.clear(__SCORE_ISSET_ID);
  }

  /** Returns true if field score is set (has been assigned a value) and false otherwise */
  public boolean isSetScore() {
    return __isset_bit_vector.get(__SCORE_ISSET_ID);
  }

  public void setScoreIsSet(boolean value) {
    __isset_bit_vector.set(__SCORE_ISSET_ID, value);
  }

  public String getProvider() {
    return this.provider;
  }

  public RecommendItem setProvider(String provider) {
    this.provider = provider;
    return this;
  }

  public void unsetProvider() {
    this.provider = null;
  }

  /** Returns true if field provider is set (has been assigned a value) and false otherwise */
  public boolean isSetProvider() {
    return this.provider != null;
  }

  public void setProviderIsSet(boolean value) {
    if (!value) {
      this.provider = null;
    }
  }

  public int getDetailSize() {
    return (this.detail == null) ? 0 : this.detail.size();
  }

  public void putToDetail(String key, String val) {
    if (this.detail == null) {
      this.detail = new HashMap<String,String>();
    }
    this.detail.put(key, val);
  }

  public Map<String,String> getDetail() {
    return this.detail;
  }

  public RecommendItem setDetail(Map<String,String> detail) {
    this.detail = detail;
    return this;
  }

  public void unsetDetail() {
    this.detail = null;
  }

  /** Returns true if field detail is set (has been assigned a value) and false otherwise */
  public boolean isSetDetail() {
    return this.detail != null;
  }

  public void setDetailIsSet(boolean value) {
    if (!value) {
      this.detail = null;
    }
  }

  public void setFieldValue(_Fields field, Object value) {
    switch (field) {
    case ID:
      if (value == null) {
        unsetId();
      } else {
        setId((String)value);
      }
      break;

    case SCORE:
      if (value == null) {
        unsetScore();
      } else {
        setScore((Double)value);
      }
      break;

    case PROVIDER:
      if (value == null) {
        unsetProvider();
      } else {
        setProvider((String)value);
      }
      break;

    case DETAIL:
      if (value == null) {
        unsetDetail();
      } else {
        setDetail((Map<String,String>)value);
      }
      break;

    }
  }

  public Object getFieldValue(_Fields field) {
    switch (field) {
    case ID:
      return getId();

    case SCORE:
      return Double.valueOf(getScore());

    case PROVIDER:
      return getProvider();

    case DETAIL:
      return getDetail();

    }
    throw new IllegalStateException();
  }

  /** Returns true if field corresponding to fieldID is set (has been assigned a value) and false otherwise */
  public boolean isSet(_Fields field) {
    if (field == null) {
      throw new IllegalArgumentException();
    }

    switch (field) {
    case ID:
      return isSetId();
    case SCORE:
      return isSetScore();
    case PROVIDER:
      return isSetProvider();
    case DETAIL:
      return isSetDetail();
    }
    throw new IllegalStateException();
  }

  @Override
  public boolean equals(Object that) {
    if (that == null)
      return false;
    if (that instanceof RecommendItem)
      return this.equals((RecommendItem)that);
    return false;
  }

  public boolean equals(RecommendItem that) {
    if (that == null)
      return false;

    boolean this_present_id = true && this.isSetId();
    boolean that_present_id = true && that.isSetId();
    if (this_present_id || that_present_id) {
      if (!(this_present_id && that_present_id))
        return false;
      if (!this.id.equals(that.id))
        return false;
    }

    boolean this_present_score = true;
    boolean that_present_score = true;
    if (this_present_score || that_present_score) {
      if (!(this_present_score && that_present_score))
        return false;
      if (this.score != that.score)
        return false;
    }

    boolean this_present_provider = true && this.isSetProvider();
    boolean that_present_provider = true && that.isSetProvider();
    if (this_present_provider || that_present_provider) {
      if (!(this_present_provider && that_present_provider))
        return false;
      if (!this.provider.equals(that.provider))
        return false;
    }

    boolean this_present_detail = true && this.isSetDetail();
    boolean that_present_detail = true && that.isSetDetail();
    if (this_present_detail || that_present_detail) {
      if (!(this_present_detail && that_present_detail))
        return false;
      if (!this.detail.equals(that.detail))
        return false;
    }

    return true;
  }

  @Override
  public int hashCode() {
    return 0;
  }

  public int compareTo(RecommendItem other) {
    if (!getClass().equals(other.getClass())) {
      return getClass().getName().compareTo(other.getClass().getName());
    }

    int lastComparison = 0;
    RecommendItem typedOther = (RecommendItem)other;

    lastComparison = Boolean.valueOf(isSetId()).compareTo(typedOther.isSetId());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetId()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.id, typedOther.id);
      if (lastComparison != 0) {
        return lastComparison;
      }
    }
    lastComparison = Boolean.valueOf(isSetScore()).compareTo(typedOther.isSetScore());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetScore()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.score, typedOther.score);
      if (lastComparison != 0) {
        return lastComparison;
      }
    }
    lastComparison = Boolean.valueOf(isSetProvider()).compareTo(typedOther.isSetProvider());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetProvider()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.provider, typedOther.provider);
      if (lastComparison != 0) {
        return lastComparison;
      }
    }
    lastComparison = Boolean.valueOf(isSetDetail()).compareTo(typedOther.isSetDetail());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetDetail()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.detail, typedOther.detail);
      if (lastComparison != 0) {
        return lastComparison;
      }
    }
    return 0;
  }

  public _Fields fieldForId(int fieldId) {
    return _Fields.findByThriftId(fieldId);
  }

  public void read(org.apache.thrift.protocol.TProtocol iprot) throws org.apache.thrift.TException {
    schemes.get(iprot.getScheme()).getScheme().read(iprot, this);
  }

  public void write(org.apache.thrift.protocol.TProtocol oprot) throws org.apache.thrift.TException {
    schemes.get(oprot.getScheme()).getScheme().write(oprot, this);
  }

  @Override
  public String toString() {
    StringBuilder sb = new StringBuilder("RecommendItem(");
    boolean first = true;

    sb.append("id:");
    if (this.id == null) {
      sb.append("null");
    } else {
      sb.append(this.id);
    }
    first = false;
    if (!first) sb.append(", ");
    sb.append("score:");
    sb.append(this.score);
    first = false;
    if (!first) sb.append(", ");
    sb.append("provider:");
    if (this.provider == null) {
      sb.append("null");
    } else {
      sb.append(this.provider);
    }
    first = false;
    if (!first) sb.append(", ");
    sb.append("detail:");
    if (this.detail == null) {
      sb.append("null");
    } else {
      sb.append(this.detail);
    }
    first = false;
    sb.append(")");
    return sb.toString();
  }

  public void validate() throws org.apache.thrift.TException {
    // check for required fields
  }

  private void writeObject(java.io.ObjectOutputStream out) throws java.io.IOException {
    try {
      write(new org.apache.thrift.protocol.TCompactProtocol(new org.apache.thrift.transport.TIOStreamTransport(out)));
    } catch (org.apache.thrift.TException te) {
      throw new java.io.IOException(te);
    }
  }

  private void readObject(java.io.ObjectInputStream in) throws java.io.IOException, ClassNotFoundException {
    try {
      // it doesn't seem like you should have to do this, but java serialization is wacky, and doesn't call the default constructor.
      __isset_bit_vector = new BitSet(1);
      read(new org.apache.thrift.protocol.TCompactProtocol(new org.apache.thrift.transport.TIOStreamTransport(in)));
    } catch (org.apache.thrift.TException te) {
      throw new java.io.IOException(te);
    }
  }

  private static class RecommendItemStandardSchemeFactory implements SchemeFactory {
    public RecommendItemStandardScheme getScheme() {
      return new RecommendItemStandardScheme();
    }
  }

  private static class RecommendItemStandardScheme extends StandardScheme<RecommendItem> {

    public void read(org.apache.thrift.protocol.TProtocol iprot, RecommendItem struct) throws org.apache.thrift.TException {
      org.apache.thrift.protocol.TField schemeField;
      iprot.readStructBegin();
      while (true)
      {
        schemeField = iprot.readFieldBegin();
        if (schemeField.type == org.apache.thrift.protocol.TType.STOP) { 
          break;
        }
        switch (schemeField.id) {
          case 1: // ID
            if (schemeField.type == org.apache.thrift.protocol.TType.STRING) {
              struct.id = iprot.readString();
              struct.setIdIsSet(true);
            } else { 
              org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
            }
            break;
          case 2: // SCORE
            if (schemeField.type == org.apache.thrift.protocol.TType.DOUBLE) {
              struct.score = iprot.readDouble();
              struct.setScoreIsSet(true);
            } else { 
              org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
            }
            break;
          case 3: // PROVIDER
            if (schemeField.type == org.apache.thrift.protocol.TType.STRING) {
              struct.provider = iprot.readString();
              struct.setProviderIsSet(true);
            } else { 
              org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
            }
            break;
          case 4: // DETAIL
            if (schemeField.type == org.apache.thrift.protocol.TType.MAP) {
              {
                org.apache.thrift.protocol.TMap _map0 = iprot.readMapBegin();
                struct.detail = new HashMap<String,String>(2*_map0.size);
                for (int _i1 = 0; _i1 < _map0.size; ++_i1)
                {
                  String _key2; // required
                  String _val3; // required
                  _key2 = iprot.readString();
                  _val3 = iprot.readString();
                  struct.detail.put(_key2, _val3);
                }
                iprot.readMapEnd();
              }
              struct.setDetailIsSet(true);
            } else { 
              org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
            }
            break;
          default:
            org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
        }
        iprot.readFieldEnd();
      }
      iprot.readStructEnd();

      // check for required fields of primitive type, which can't be checked in the validate method
      struct.validate();
    }

    public void write(org.apache.thrift.protocol.TProtocol oprot, RecommendItem struct) throws org.apache.thrift.TException {
      struct.validate();

      oprot.writeStructBegin(STRUCT_DESC);
      if (struct.id != null) {
        oprot.writeFieldBegin(ID_FIELD_DESC);
        oprot.writeString(struct.id);
        oprot.writeFieldEnd();
      }
      oprot.writeFieldBegin(SCORE_FIELD_DESC);
      oprot.writeDouble(struct.score);
      oprot.writeFieldEnd();
      if (struct.provider != null) {
        oprot.writeFieldBegin(PROVIDER_FIELD_DESC);
        oprot.writeString(struct.provider);
        oprot.writeFieldEnd();
      }
      if (struct.detail != null) {
        oprot.writeFieldBegin(DETAIL_FIELD_DESC);
        {
          oprot.writeMapBegin(new org.apache.thrift.protocol.TMap(org.apache.thrift.protocol.TType.STRING, org.apache.thrift.protocol.TType.STRING, struct.detail.size()));
          for (Map.Entry<String, String> _iter4 : struct.detail.entrySet())
          {
            oprot.writeString(_iter4.getKey());
            oprot.writeString(_iter4.getValue());
          }
          oprot.writeMapEnd();
        }
        oprot.writeFieldEnd();
      }
      oprot.writeFieldStop();
      oprot.writeStructEnd();
    }

  }

  private static class RecommendItemTupleSchemeFactory implements SchemeFactory {
    public RecommendItemTupleScheme getScheme() {
      return new RecommendItemTupleScheme();
    }
  }

  private static class RecommendItemTupleScheme extends TupleScheme<RecommendItem> {

    @Override
    public void write(org.apache.thrift.protocol.TProtocol prot, RecommendItem struct) throws org.apache.thrift.TException {
      TTupleProtocol oprot = (TTupleProtocol) prot;
      BitSet optionals = new BitSet();
      if (struct.isSetId()) {
        optionals.set(0);
      }
      if (struct.isSetScore()) {
        optionals.set(1);
      }
      if (struct.isSetProvider()) {
        optionals.set(2);
      }
      if (struct.isSetDetail()) {
        optionals.set(3);
      }
      oprot.writeBitSet(optionals, 4);
      if (struct.isSetId()) {
        oprot.writeString(struct.id);
      }
      if (struct.isSetScore()) {
        oprot.writeDouble(struct.score);
      }
      if (struct.isSetProvider()) {
        oprot.writeString(struct.provider);
      }
      if (struct.isSetDetail()) {
        {
          oprot.writeI32(struct.detail.size());
          for (Map.Entry<String, String> _iter5 : struct.detail.entrySet())
          {
            oprot.writeString(_iter5.getKey());
            oprot.writeString(_iter5.getValue());
          }
        }
      }
    }

    @Override
    public void read(org.apache.thrift.protocol.TProtocol prot, RecommendItem struct) throws org.apache.thrift.TException {
      TTupleProtocol iprot = (TTupleProtocol) prot;
      BitSet incoming = iprot.readBitSet(4);
      if (incoming.get(0)) {
        struct.id = iprot.readString();
        struct.setIdIsSet(true);
      }
      if (incoming.get(1)) {
        struct.score = iprot.readDouble();
        struct.setScoreIsSet(true);
      }
      if (incoming.get(2)) {
        struct.provider = iprot.readString();
        struct.setProviderIsSet(true);
      }
      if (incoming.get(3)) {
        {
          org.apache.thrift.protocol.TMap _map6 = new org.apache.thrift.protocol.TMap(org.apache.thrift.protocol.TType.STRING, org.apache.thrift.protocol.TType.STRING, iprot.readI32());
          struct.detail = new HashMap<String,String>(2*_map6.size);
          for (int _i7 = 0; _i7 < _map6.size; ++_i7)
          {
            String _key8; // required
            String _val9; // required
            _key8 = iprot.readString();
            _val9 = iprot.readString();
            struct.detail.put(_key8, _val9);
          }
        }
        struct.setDetailIsSet(true);
      }
    }
  }

}
