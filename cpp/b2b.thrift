////////////////////////////////////////////////////////////////////////
///	@file    b2b.thrift
///	@brief   定义blocknode到blocknode的通信
///	@author  liuyanchen@snda.com
///	@date 	  2011-04-20
///	@version 1.0	
////////////////////////////////////////////////////////////////////////

include "common.thrift"

namespace cpp ebs.common

///	定义blocknode之间的调用
service B2BProtocol {
    ///获取副本的版本号
	i64 getVersion(1:string blockId) throws (1:common.EbsException ouch),

    ///获取Volume的块的子版本号
	list<i64> getBlockVersions(1:string blockId, 2:list<common.BlockData> blockData) throws (1:common.EbsException ouch),
	
	///发送同步数据
    ///version: 当前发送的queue的版本
	void sendData(1:string volumeId, 2:i64 version, 3:list<i64> queueSize, 4:list<common.BlockData> queueData) throws (1:common.EbsException ouch),

	///块复制
	///blockVersion
	/// >0: update blockVersion
	///updateVersion
	/// >0: update updateVersion of volume
	void copyData(1:string volumeId, 2:i64 updateVersion, 3:i64 blockVersion, 4:common.BlockData blockData) throws (1:common.EbsException ouch),
	
	///不需要更新数据则返回0，需要更新数据则返回从副本当前的版本号		
	i64 detachSecondary(1:string blockId,2:i32 token,3:i64 version) throws (1:common.EbsException ouch),
	
	void dumpFile() throws (1:common.EbsException ouch),
}
