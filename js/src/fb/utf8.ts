// automatically generated by the FlatBuffers compiler, do not modify

import * as flatbuffers from 'flatbuffers';

/**
 * Unicode with UTF-8 encoding
 */
export class Utf8 {
  bb: flatbuffers.ByteBuffer|null = null;
  bb_pos = 0;
__init(i:number, bb:flatbuffers.ByteBuffer):Utf8 {
  this.bb_pos = i;
  this.bb = bb;
  return this;
}

static getRootAsUtf8(bb:flatbuffers.ByteBuffer, obj?:Utf8):Utf8 {
  return (obj || new Utf8()).__init(bb.readInt32(bb.position()) + bb.position(), bb);
}

static getSizePrefixedRootAsUtf8(bb:flatbuffers.ByteBuffer, obj?:Utf8):Utf8 {
  bb.setPosition(bb.position() + flatbuffers.SIZE_PREFIX_LENGTH);
  return (obj || new Utf8()).__init(bb.readInt32(bb.position()) + bb.position(), bb);
}

static startUtf8(builder:flatbuffers.Builder) {
  builder.startObject(0);
}

static endUtf8(builder:flatbuffers.Builder):flatbuffers.Offset {
  const offset = builder.endObject();
  return offset;
}

static createUtf8(builder:flatbuffers.Builder):flatbuffers.Offset {
  Utf8.startUtf8(builder);
  return Utf8.endUtf8(builder);
}
}
