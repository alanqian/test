#ifndef _HS_HASH_TMPL_
#define _HS_HASH_TMPL_

#	if	(defined(_MSC_VER) && _MSC_VER < 1300 )
#		error	Not Supported for MS VC6!
#	endif

#include <hsutil.h>
#include <hscplex.h>
#include <assert.h>

/** template HS_HashKey
 *
 *  为处理 Hash Key 所写的template, 主要提供：
 *  1. 计算Key的Hash值
 *  2. 释入Key所有资源
 *  3. 比较两个Key是否相等
 *  4. 复制Key
 *
 *  如果KEY是一个类，则要求此类：
 *  1. 提供 operator == ,  以判断两个对象是否相等
 *  2. 重载 operator unsigned int () const , 以计算此对象的Hash值
 *
 *  在使用 template HS_Hash 时，必需提供一个类似于HS_HashKey的template，
 *  如有特殊需要，你可以针对KEY特化template HS_HashKey， 也可提供一个全新的template
 */
template <class KEY>
class HS_HashKey
{
public:
	inline static void KeyDelete(KEY &key) { };
	inline static void KeyCopy(KEY &key,  const KEY &newkey)
	{
		key = newkey;
	};
	inline static bool KeyCompare( const KEY &key1, const KEY &key2)
	{
		return key1==key2;
	};
	inline static unsigned int KeyHash( const KEY &key)
	{
		return (unsigned int)key;
	}
	inline static unsigned int KeyHash( const KEY &key, int)
	{
		return (unsigned int)key;
	}
};

template<>
class HS_HashKey<char*>
{
public:
	inline static void KeyDelete(char* &key) 
	{
		delete []key;
		key = NULL;
	};
	inline static void KeyCopy(char* &key,  const char* &newkey)
	{
		key = new char[strlen(newkey)+1];
		strcpy(key, newkey);
	};
	inline static bool KeyCompare( const char* &key1, const char* &key2)
	{
		return strcmp(key1, key2) == 0;
	};
	inline static unsigned int KeyHash( const char* &lkey)	///使大小写不一致的串的Hash值完全一致
	{
		unsigned int nHash = 0;
		const char* key = lkey;
		while (*key)
			nHash = (nHash<<5) + nHash + *key++;
		return nHash;
	}
	inline static unsigned int KeyHash( const char* &key, int)
	{
		return KeyHash(key);
	}
};

template<>
class HS_HashKey<HSUINT16*>
{
public:
	inline static void	HS_HashKey<HSUINT16*>::KeyDelete(HSUINT16* &key)
	{
		delete []key;
		key = NULL;
	}

	inline static void	HS_HashKey<HSUINT16*>::KeyCopy(HSUINT16* &key,  HSUINT16* const&newkey)
	{
		key = new HSUINT16[hnstrlen(newkey)+1];
		hnstrcpy(key, newkey);
	}

	inline static bool	HS_HashKey<HSUINT16*>::KeyCompare( HSUINT16* const&key1,  HSUINT16* const&key2)
	{
		return hnstrcmp(key1, key2) == 0;
	}

	inline static unsigned int HS_HashKey<HSUINT16*>::KeyHash( HSUINT16* const&lkey)
	{
		unsigned int nHash = 0;
		const HSUINT16* key = lkey;
		while (*key)
			nHash = (nHash<<5) + nHash + *key++;
		return nHash;
	}
};

template<class> class HS_HashNoCaseStrKey;		/// 只声明不定义，使其只用于char*的特化版本
template<>
class HS_HashNoCaseStrKey<char*>
{
public:
	inline static void KeyDelete(char* &key) 
	{
		delete []key;
		key = NULL;
	};
	inline static void KeyCopy(char* &key,  const char* &newkey)
	{
		key = new char[strlen(newkey)+1];
		strcpy(key, newkey);
	};
	inline static bool KeyCompare( const char* &key1, const char* &key2)
	{
		return strcmp(key1, key2) == 0;
	};
	inline static unsigned int KeyHash( const char* &lkey)	///使大小写不一致的串的Hash值完全一致
	{
		unsigned int nHash = 0;
		const char* key = lkey;
		while (*key)
		{
			if(*key >= 'A' && *key <= 'Z')
				nHash = (nHash<<5) + nHash + ('a'-'A') + *key++;
			else
				nHash = (nHash<<5) + nHash + *key++;
		}
		return nHash;
	}
	inline static unsigned int KeyHash( const char* &key, int)
	{
		return KeyHash(key);
	}
};

#define HASH_MOD(x,y)                  ((x) & ((y)-1))
#define HASH_MAX_TABLESIZE             0x4000000
#define HASH_MAX_SEGSIZE               4096
#define HASH_MAX_DIRSIZE               2048
#define HASH_MAX_FFACTOR               1	// 平均每桶有1个元素

/**
 * templats Hash
 * 这里实现的是动态Hash
 */
template <class KEY, class VALUE, template<class> class HASHKEY=HS_HashKey, bool DynHash=true>
class HS_Hash : public HASHKEY<KEY>
{
protected:
	struct CDynHashHead
	{
		long			dsize;			/* Directory Size */
		long			ssize;			/* Segment Size --- must be power of 2 */
		int				sshift;			/* Segment shift = log2(ssize) */
		unsigned int	max_bucket;		/* ID of Maximum bucket in use */
		unsigned int	high_mask;		/* Mask to modulo into entire table */
		unsigned int	low_mask;		/* Mask to modulo into lower half of table */
		long			ffactor;		/* Fill factor */
		long			nentries;		/* Number of entries in hash table */
		long			nsegs;			/* Number of allocated segments */

		int				entrysize;		/* total user element size in bytes */
	};

	struct CAssoc
	{
		CAssoc* pNext;
		unsigned int nHashValue;  
		KEY key;
		VALUE value;
	};
	
	CAssoc***	m_pDir;
	CAssoc*		m_pFreeList;
	struct HS_CPlex* m_pBlocks;

	CDynHashHead  m_ctl;	

protected:
	CAssoc* NewAssoc();
	void FreeAssoc(CAssoc*);
	CAssoc* GetAssocAt(KEY, unsigned int&) const;

public:
	HS_Hash(int nBlockSize = HASH_MAX_SEGSIZE/4, int nDirSize=HASH_MAX_DIRSIZE/2, int nFFactor=HASH_MAX_FFACTOR);
	~HS_Hash();
	void	InitHashTable(unsigned int nSegSize, bool bAllocNow = true);
	void	SetHashTableSize(int nSegSize);

	int		FindValideHashTableSizse(int orgTableSize) const;
	int		GetCount() const;
	int		GetHashTableSize() const { return m_ctl.max_bucket + 1; }
	bool	IsEmpty() const;
	
	VALUE&	operator[](KEY key);
	bool	SetAt(KEY key, VALUE newValue);

	virtual bool	RemoveKey(KEY key);
	void	RemoveBuckets();
	void	RemoveAll();

	bool	Lookup(KEY key, VALUE& rValue) const;
	HS_POSITION	GetStartPosition() const;
	void	GetNextAssoc(HS_POSITION& rNextPosition, KEY& rKey, VALUE& rValue) const;

protected:
	bool	ExpendHashTable();

	int		my_log2(long num) const;
	unsigned int CalBucket(unsigned int nHashValue) const;
};

template <class KEY, class VALUE, template<class> class HASHKEY, bool DynHash>
int		HS_Hash<KEY, VALUE, HASHKEY, DynHash>::my_log2(long num) const
{
	int			i;
	long		limit;
	for (i = 0, limit = 1; limit < num; i++, limit <<= 1)
		;
	return i;
}

template <class KEY, class VALUE, template<class> class HASHKEY, bool DynHash>
unsigned int HS_Hash<KEY, VALUE, HASHKEY, DynHash>::CalBucket(unsigned int nHashValue) const
{
	unsigned int		bucket;	
	bucket = nHashValue & m_ctl.high_mask;
	if (bucket > m_ctl.max_bucket)
		bucket = bucket & m_ctl.low_mask;
	return bucket;
}

template <class KEY, class VALUE, template<class> class HASHKEY, bool DynHash>
int	 HS_Hash<KEY, VALUE, HASHKEY, DynHash>::FindValideHashTableSizse(int orgTableSize) const
{
	return 1 << my_log2(orgTableSize);
}

template <class KEY, class VALUE, template<class> class HASHKEY, bool DynHash>
HS_Hash<KEY, VALUE, HASHKEY, DynHash>::HS_Hash(int nSegSize, int nDirSize, int nFFactor)
{
	memset(&m_ctl, 0, sizeof(m_ctl));
	m_pDir = NULL;
	m_pFreeList = NULL;
	m_pBlocks = NULL;

	if(nDirSize > HASH_MAX_DIRSIZE)
		nDirSize = HASH_MAX_DIRSIZE;
	m_ctl.dsize = nDirSize;
	m_ctl.ffactor = nFFactor;
	m_ctl.entrysize = sizeof(CAssoc);
	InitHashTable (nSegSize, false);
}

template <class KEY, class VALUE, template<class> class HASHKEY, bool DynHash>
HS_Hash<KEY, VALUE, HASHKEY, DynHash>::~HS_Hash()
{
	RemoveAll();
}

template <class KEY, class VALUE, template<class> class HASHKEY, bool DynHash>
void HS_Hash<KEY, VALUE, HASHKEY, DynHash>::InitHashTable(unsigned int nSegSize, bool bAllocNow)
{
	if( m_pDir )
		RemoveAll();

	if(nSegSize > HASH_MAX_SEGSIZE)
		nSegSize = HASH_MAX_SEGSIZE;

	m_ctl.ssize = (1 << my_log2(nSegSize));
	m_ctl.sshift = my_log2(m_ctl.ssize);

	int		nbuckets;
	int		nsegs=0;
	int		nelem=nSegSize;

	/**
	 * Divide number of elements by the fill factor to determine a desired
	 * number of buckets.  Allocate space for the next greater power of
	 * two number of buckets
	 */
	nelem = (nelem - 1) / m_ctl.ffactor + 1;
	nbuckets = 1 << my_log2(nelem);    /// N

	m_ctl.max_bucket = m_ctl.low_mask = nbuckets - 1;
	m_ctl.high_mask = (nbuckets << 1) - 1;

	if(bAllocNow)
	{
		/**
		* Figure number of directory segments needed, round up to a power of 2
		*/
		nsegs = m_ctl.max_bucket / m_ctl.ssize + 1;
		nsegs = 1 << my_log2(nsegs);

		/**
		* Make sure directory is big enough. If pre-allocated directory is
		* too small, choke (caller screwed up).
		*/
		if (nsegs > m_ctl.dsize)
		{
			m_ctl.dsize = nsegs;
		}

		/** Allocate a directory */
		m_pDir = new CAssoc** [m_ctl.dsize];
		memset(m_pDir, 0, sizeof(CAssoc**) * m_ctl.dsize);

		/** Allocate initial segments */
		m_ctl.nsegs = nsegs;
		for (nsegs=0;  nsegs<m_ctl.nsegs; nsegs++)
		{
			m_pDir[nsegs] = new CAssoc* [m_ctl.ssize]; //SegmentAlloc();
			memset(m_pDir[nsegs], 0, sizeof(CAssoc*) * m_ctl.ssize);
		}
	}
}

template <class KEY, class VALUE, template<class> class HASHKEY, bool DynHash>
void HS_Hash<KEY, VALUE, HASHKEY, DynHash>::SetHashTableSize(int nSegSize)
{
	InitHashTable(nSegSize, false);
}

template <class KEY, class VALUE, template<class> class HASHKEY, bool DynHash>
int HS_Hash<KEY, VALUE, HASHKEY, DynHash>::GetCount()const
{
	return m_ctl.nentries;
}

template <class KEY, class VALUE, template<class> class HASHKEY, bool DynHash>
bool HS_Hash<KEY, VALUE, HASHKEY, DynHash>::IsEmpty() const
{
	return m_ctl.nentries == 0;
}

template <class KEY, class VALUE, template<class> class HASHKEY, bool DynHash>
bool HS_Hash<KEY, VALUE, HASHKEY, DynHash>::Lookup(KEY key, VALUE& rValue) const 
{
	unsigned int nHashValue;
	CAssoc* pAssoc = GetAssocAt(key, nHashValue);
	if (pAssoc == NULL)
		return false;  // not in map
	
	rValue = pAssoc->value;
	return true;
}

template <class KEY, class VALUE, template<class> class HASHKEY, bool DynHash>
bool HS_Hash<KEY, VALUE, HASHKEY, DynHash>::SetAt(KEY key, VALUE newValue)
{
	int nPreCount =  GetCount();
	(*this)[key] = newValue;
	return nPreCount < GetCount();
}

template <class KEY, class VALUE, template<class> class HASHKEY, bool DynHash>
void HS_Hash<KEY, VALUE, HASHKEY, DynHash>::RemoveAll()
{
	if (m_pDir != NULL)
	{
		unsigned int segment_num;
		unsigned int segment_ndx;
		CAssoc* pAssoc;

		for (unsigned int nBucket = 0; nBucket < m_ctl.max_bucket + 1; nBucket++)
		{
			segment_num = nBucket >> m_ctl.sshift;
			segment_ndx = HASH_MOD(nBucket, m_ctl.ssize);
			for (pAssoc = m_pDir[segment_num][segment_ndx]; pAssoc != NULL; pAssoc = pAssoc->pNext)
			{
				KeyDelete(pAssoc->key);  // free up string data
			}
		}
		
		for (long segno=0; segno < m_ctl.nsegs; segno++)
		{
			delete[] m_pDir[segno];
		}

		delete[] m_pDir;
		m_pDir = NULL;
	}
	// free hash table
	
	m_ctl.nentries = 0;

	m_pFreeList = NULL;
	m_pBlocks->FreeDataChain();
	m_pBlocks = NULL;
}

template <class KEY, class VALUE, template<class> class HASHKEY, bool DynHash>
void HS_Hash<KEY, VALUE, HASHKEY, DynHash>::RemoveBuckets()
{
	if (m_pDir != NULL)
	{
		for (long segno=0; segno < m_ctl.nsegs; segno++)
		{
			delete[] m_pDir[segno];
		}

		delete [] m_pDir;
		m_pDir = NULL;
	}

	m_ctl.nentries = 0;
	m_pFreeList = NULL;
	m_pBlocks->FreeDataChain();
	m_pBlocks = NULL;
}

// iterating all (key, value) pairs
template <class KEY, class VALUE, template<class> class HASHKEY, bool DynHash>
HS_POSITION HS_Hash<KEY, VALUE, HASHKEY, DynHash>::GetStartPosition() const
{
	return (m_ctl.nentries == 0) ? NULL : HS_BEFORE_START_POSITION; 	
}

template <class KEY, class VALUE, template<class> class HASHKEY, bool DynHash>
VALUE& HS_Hash<KEY, VALUE, HASHKEY, DynHash>::operator[](KEY key)
{
	CAssoc* pAssoc;
	unsigned int nHashValue;
	if ((pAssoc = GetAssocAt(key, nHashValue)) == NULL)
	{
		if (m_pDir == NULL)
			InitHashTable(m_ctl.ssize);
		
		// it doesn't exist, add a new Association
		pAssoc = NewAssoc();
		
		assert(pAssoc!= NULL);
		
		pAssoc->nHashValue = nHashValue;
		unsigned int nBucket = CalBucket(nHashValue);
		KeyCopy(pAssoc->key, key);
		// 'pAssoc->value' is a constructed object, nothing more

		unsigned int segment_num = nBucket >> m_ctl.sshift;
		unsigned int segment_ndx = HASH_MOD(nBucket, m_ctl.ssize);

		//将它插入到这个桶的头位置
		pAssoc->pNext = m_pDir[segment_num][segment_ndx];
		m_pDir[segment_num][segment_ndx] = pAssoc;
		
		//m_ctl.nentries ++;
		//if((float)(m_ctl.nentries) /(float)((m_ctl.max_bucket +1))>m_ctl.ffactor )//应该分裂了。
		if( m_ctl.nentries < HASH_MAX_TABLESIZE &&
			(unsigned)m_ctl.nentries > (m_ctl.max_bucket +1) * m_ctl.ffactor )//应该分裂了。
			ExpendHashTable();
	}
	return pAssoc->value;  // return new reference
}

// remove key - return true if removed
template <class KEY, class VALUE, template<class> class HASHKEY, bool DynHash>
bool HS_Hash<KEY, VALUE, HASHKEY, DynHash>::RemoveKey(KEY key)
{
	if (m_pDir == NULL)
		return false;  // nothing in the table
	
	CAssoc** ppAssocPrev;

	unsigned int nHashValue = KeyHash(key);
	unsigned int nBucket = CalBucket(nHashValue);
	unsigned int segment_num = nBucket >> m_ctl.sshift;
	unsigned int segment_ndx = HASH_MOD(nBucket, m_ctl.ssize);

	ppAssocPrev = &m_pDir[segment_num][segment_ndx];
	
	CAssoc* pAssoc;
	for (pAssoc = *ppAssocPrev; pAssoc != NULL; pAssoc = pAssoc->pNext)
	{
		//if (KeyCompare(&pAssoc->key, &key))
		if (pAssoc->nHashValue == nHashValue &&
			KeyCompare(pAssoc->key, key))
		{
			// remove it
			*ppAssocPrev = pAssoc->pNext;  // remove from list
			FreeAssoc(pAssoc);
			return true;
		}
		ppAssocPrev = &pAssoc->pNext;
	}
	return false;  // not found
}

template <class KEY, class VALUE, template<class> class HASHKEY, bool DynHash>
void HS_Hash<KEY, VALUE, HASHKEY, DynHash>::GetNextAssoc(HS_POSITION& rNextPosition,
									   KEY& rKey, VALUE& rValue) const
{
	assert(m_pDir != NULL);  // never call on empty map
	
	CAssoc* pAssocRet = (CAssoc*)rNextPosition;
	assert(pAssocRet != NULL);
	unsigned int segment_num;
	unsigned int segment_ndx;
	
	if (pAssocRet == (CAssoc*) HS_BEFORE_START_POSITION)
	{
		// find the first association
		for (unsigned int nBucket = 0; nBucket < m_ctl.max_bucket+1; nBucket++)
		{
			segment_num = nBucket >> m_ctl.sshift;
			segment_ndx = HASH_MOD(nBucket, m_ctl.ssize);

			if ((pAssocRet = m_pDir[segment_num][segment_ndx]) != NULL)
				break;
		}
		assert(pAssocRet != NULL);  // must find something
	}
	
	// find next association
	CAssoc* pAssocNext;
	if ((pAssocNext = pAssocRet->pNext) == NULL)
	{
		// go to next bucket
		for (unsigned int nBucket = CalBucket(pAssocRet->nHashValue) + 1;
			nBucket < m_ctl.max_bucket+1; nBucket++)
		{
			segment_num = nBucket >> m_ctl.sshift;
			segment_ndx = HASH_MOD(nBucket, m_ctl.ssize);

			if ((pAssocNext = m_pDir[segment_num][segment_ndx]) != NULL)
				break;
		}
	}
	
	rNextPosition = (HS_POSITION) pAssocNext;
	
	// fill in return data
	rKey = pAssocRet->key;
	rValue = pAssocRet->value;
}

// find association (or return NULL)
template <class KEY, class VALUE, template<class> class HASHKEY, bool DynHash>
typename HS_Hash<KEY, VALUE, HASHKEY, DynHash>::CAssoc* 
HS_Hash<KEY, VALUE, HASHKEY, DynHash>::GetAssocAt(KEY key, unsigned int& nHashValue)const
{
	nHashValue = KeyHash(key);
	if (m_pDir == NULL)
		return NULL;	
	unsigned int nBucket = CalBucket(nHashValue);
	unsigned int segment_num = nBucket >> m_ctl.sshift;
	unsigned int segment_ndx = HASH_MOD(nBucket, m_ctl.ssize);

	CAssoc* pAssoc;
	for (pAssoc = m_pDir[segment_num][segment_ndx]; pAssoc != NULL; pAssoc = pAssoc->pNext)
	{
		if (pAssoc->nHashValue == nHashValue &&
			KeyCompare(pAssoc->key, key))
			//if (pAssoc->key ==  key )
			return pAssoc;
	}
	return NULL;
}

template <class KEY, class VALUE, template<class> class HASHKEY, bool DynHash>
void HS_Hash<KEY, VALUE, HASHKEY, DynHash>::FreeAssoc(typename HS_Hash<KEY, VALUE, HASHKEY, DynHash>::CAssoc* pAssoc)
{
	KeyDelete(pAssoc->key);
	
	pAssoc->pNext = m_pFreeList;
	m_pFreeList = pAssoc;
	m_ctl.nentries--;
	assert(m_ctl.nentries >= 0);  // make sure we don't underflow
	
	// if no more elements, cleanup completely
	if (m_ctl.nentries == 0)
		RemoveBuckets();
}

template <class KEY, class VALUE, template<class> class HASHKEY, bool DynHash>
typename HS_Hash<KEY, VALUE, HASHKEY, DynHash>::CAssoc*
HS_Hash<KEY, VALUE, HASHKEY, DynHash>::NewAssoc()
{
	if (m_pFreeList == NULL)
	{
		// add another block
		HS_CPlex* newBlock = HS_CPlex::Create(m_pBlocks, m_ctl.ssize, sizeof(HS_Hash::CAssoc));
		// chain them into free list
		HS_Hash::CAssoc* pAssoc = (HS_Hash::CAssoc*) newBlock->data();
		// free in reverse order to make it easier to debug
		pAssoc += m_ctl.ssize - 1;
		for (int i = m_ctl.ssize-1; i >= 0; i--, pAssoc--)
		{
			pAssoc->pNext = m_pFreeList;
			m_pFreeList = pAssoc;
		}
	}
	assert(m_pFreeList != NULL);  // we must have something
	
	HS_Hash::CAssoc* pAssoc = m_pFreeList;
	m_pFreeList = m_pFreeList->pNext;
	m_ctl.nentries++;
	assert(m_ctl.nentries > 0);  // make sure we don't overflow

	//pAssoc->key = NULL;
	//pAssoc->value = NULL;	
	return pAssoc;
}

template <class KEY, class VALUE, template<class> class HASHKEY, bool DynHash>
bool HS_Hash<KEY, VALUE, HASHKEY, DynHash>::ExpendHashTable()
{	
	CAssoc		**old_seg;
	CAssoc		**new_seg;
	long		old_bucket,
				new_bucket;
	long		new_segnum,
				new_segndx;
	long		old_segnum,
				old_segndx;
	
	CAssoc		*currElement;
	CAssoc		*prevElement;
	

	new_bucket = m_ctl.max_bucket + 1;
	new_segnum = new_bucket >> m_ctl.sshift;
	new_segndx = HASH_MOD(new_bucket, m_ctl.ssize);

	if (new_segnum >= m_ctl.nsegs)//应该分配新的段了。
	{		
		if (new_segnum >= m_ctl.dsize)
		{
			CAssoc*** pTmpDir = new CAssoc** [m_ctl.dsize*2];
			if(!pTmpDir)
				return false;
			memmove(pTmpDir, m_pDir, sizeof(CAssoc**) * m_ctl.dsize);
			memset(pTmpDir + m_ctl.dsize, 0, sizeof(CAssoc**) * m_ctl.dsize);
			delete [] m_pDir;
			m_pDir = pTmpDir;
			m_ctl.dsize <<= 1; //m_ctl.dsize *= 2;
            
			if (new_segnum >= m_ctl.dsize) //不明原因出错，仍超过了哈希表的当前设计容量,不再进行分裂
				return false;
		}
		
		if (!(m_pDir[new_segnum] = new CAssoc* [m_ctl.ssize]))
			return false;//分配新段不成功
		memset(m_pDir[new_segnum], 0, sizeof(CAssoc*) * m_ctl.ssize);
		m_ctl.nsegs++;
	}

	/* OK, we created a new bucket */
	m_ctl.max_bucket++;


	/*
	 * *Before* changing masks, find old bucket corresponding to same hash
	 * values; values in that bucket may need to be relocated to new
	 * bucket. Note that new_bucket is certainly larger than low_mask at
	 * this point, so we can skip the first step of the regular hash mask
	 * calc.
	 */
	old_bucket = (new_bucket & m_ctl.low_mask);

	/*
	 * If we crossed a power of 2, readjust masks.
	 */
	if ((unsigned int) new_bucket > m_ctl.high_mask)
	{
		m_ctl.low_mask = m_ctl.high_mask;
		m_ctl.high_mask = (unsigned int) new_bucket | m_ctl.low_mask;
	}

	/*
	 * Relocate records to the new bucket.	NOTE: because of the way the
	 * hash masking is done in calc_bucket, only one old bucket can need to
	 * be split at this point.	With a different way of reducing the hash
	 * value, that might not be true!
	 */
	old_segnum = old_bucket >> m_ctl.sshift;
	old_segndx = HASH_MOD(old_bucket, m_ctl.ssize);

	old_seg = m_pDir[old_segnum];
	new_seg = m_pDir[new_segnum];

	prevElement=currElement = old_seg[old_segndx];
	

    while(currElement != NULL)
	{
		
		if ((long) CalBucket(currElement->nHashValue) != old_bucket)//将这个元素放入新桶之中
		{
			 CAssoc* temp;
			 temp = currElement->pNext ;

			 //将currElement插入新桶的头位置
			 currElement->pNext =new_seg[new_segndx];
             new_seg[new_segndx]=currElement;

			 //currElment是这个桶的的第一个元素
			 if(currElement==prevElement)
			 {
				 old_seg[old_segndx]=temp;
				 prevElement=currElement = old_seg[old_segndx];
			 }
			 else//不是第一个元素
			 {
				 prevElement->pNext = temp;
				 currElement=temp;
			 }
		}
		else
		{
			prevElement=currElement;
			currElement=currElement->pNext;
		}
	}

	return true;
}

/**
 *  静态Hash -- HS_Hash类的特化版本，
 *  如果使用此静态Hash，必须先调用SetHashTableSize 或 InitHashTable以初始化Hash表的大小
 */
template <class KEY, class VALUE, template<class> class HASHKEY>
class HS_Hash<KEY, VALUE, HASHKEY, false> : public HASHKEY<KEY>
{
protected:
	struct CAssoc
	{
		CAssoc* pNext;
		unsigned int nHashValue;  
		KEY key;
		VALUE value;
	};
	
	CAssoc**	m_pHashTable;
	int			m_nHashTableSize;
	int			m_nCount;
	CAssoc*		m_pFreeList;
	struct HS_CPlex* m_pBlocks;
	int			m_nBlockSize;
	

protected:
	CAssoc* NewAssoc();
	void FreeAssoc(CAssoc*);
	CAssoc* GetAssocAt(KEY, unsigned int&) const;

public:
	HS_Hash(int nBlockSize = 17);
	~HS_Hash();
	void	InitHashTable(unsigned int hashSize, bool bAllocNow = true);
	void	SetHashTableSize(int hashSize);

	int		FindValideHashTableSizse(int orgTableSize) const;
	int		GetCount() const;
	int		GetHashTableSize() const { return m_nHashTableSize; }
	bool	IsEmpty() const;
	
	VALUE&	operator[](KEY key);
	bool	SetAt(KEY key, VALUE newValue);

	virtual bool	RemoveKey(KEY key);
	void	RemoveBuckets();
	void	RemoveAll();

	bool	Lookup(KEY key, VALUE& rValue) const;
	HS_POSITION	GetStartPosition() const;
	void	GetNextAssoc(HS_POSITION& rNextPosition, KEY& rKey, VALUE& rValue) const;
};

template <class KEY, class VALUE, template<class> class HASHKEY>
int	 HS_Hash<KEY, VALUE, HASHKEY, false>::FindValideHashTableSizse(int orgTableSize) const
{
	int hashValue[] = { 249,251,257,503,509,521,1019,1021,1031,
		4091,4093,4099,8179,8191,8209,10223,10243,10247,20479,
		20483,	20507,40949,40961,40973,65479,	65497,	65521,
		71693,	81929,92173,102407,112643,122887,133121,143387,
		163841, 204803,256019,307201,409609,512009,614413,
		716809,819229,921601,1048583, 
		1253377,1458179,1662977,1867783,2097169,2506759,3145739,
		0,
	};
	int i = 0;
	while( hashValue[i] < orgTableSize && hashValue[i] != 0 )
		i++;
	if ( hashValue[i] == 0 )
		return orgTableSize*2 -1;
	else
		return hashValue[i];
}

template <class KEY, class VALUE, template<class> class HASHKEY>
HS_Hash<KEY, VALUE, HASHKEY, false>::HS_Hash(int nBlockSize)
{
	m_pHashTable = NULL;
	m_nHashTableSize = FindValideHashTableSizse(nBlockSize);
	m_nCount = 0;
	m_pFreeList = NULL;
	m_pBlocks = NULL;
	m_nBlockSize = m_nHashTableSize;
}

template <class KEY, class VALUE, template<class> class HASHKEY>
HS_Hash<KEY, VALUE, HASHKEY, false>::~HS_Hash()
{
	RemoveAll();
}

template <class KEY, class VALUE, template<class> class HASHKEY>
void HS_Hash<KEY, VALUE, HASHKEY, false>::InitHashTable(unsigned int hashSize, bool bAllocNow)
{
	if (m_pHashTable != NULL)
	{
		delete[] m_pHashTable;
		m_pHashTable = NULL;
	}
	
	m_nHashTableSize = FindValideHashTableSizse(hashSize);
	
	if( bAllocNow )
	{
		m_pHashTable = new CAssoc* [m_nHashTableSize];
		memset(m_pHashTable, 0, sizeof(CAssoc*) * m_nHashTableSize);
	}
	
	m_nBlockSize = m_nHashTableSize / 2;
}

template <class KEY, class VALUE, template<class> class HASHKEY>
void HS_Hash<KEY, VALUE, HASHKEY, false>::SetHashTableSize(int hashSize)
{
	InitHashTable(hashSize, true);
}

template <class KEY, class VALUE, template<class> class HASHKEY>
int HS_Hash<KEY, VALUE, HASHKEY, false>::GetCount()const
{
	return m_nCount;
}

template <class KEY, class VALUE, template<class> class HASHKEY>
bool HS_Hash<KEY, VALUE, HASHKEY, false>::IsEmpty() const
{
	return m_nCount == 0;
}

template <class KEY, class VALUE, template<class> class HASHKEY>
bool HS_Hash<KEY, VALUE, HASHKEY, false>::Lookup(KEY key, VALUE& rValue) const 
{
	unsigned int nHash;
	CAssoc* pAssoc = GetAssocAt(key, nHash);
	if (pAssoc == NULL)
		return false;  // not in map
	
	rValue = pAssoc->value;
	return true;
}

template <class KEY, class VALUE, template<class> class HASHKEY>
bool HS_Hash<KEY, VALUE, HASHKEY, false>::SetAt(KEY key, VALUE newValue)
{
	int nPreCount =  GetCount();
	(*this)[key] = newValue;
	return nPreCount < GetCount();
}

template <class KEY, class VALUE, template<class> class HASHKEY>
void HS_Hash<KEY, VALUE, HASHKEY, false>::RemoveAll()
{
	if (m_pHashTable != NULL)
	{
		for (unsigned int nHash = 0; nHash < (unsigned int)m_nHashTableSize; nHash++)
		{
			CAssoc* pAssoc;
			for (pAssoc = m_pHashTable[nHash]; pAssoc != NULL;
			pAssoc = pAssoc->pNext)
			{
				KeyDelete(pAssoc->key);  // free up string data
			}
		}
		
		delete[] m_pHashTable;
	}
	// free hash table
	m_pHashTable = NULL;
	
	m_nCount = 0;
	m_pFreeList = NULL;
	m_pBlocks->FreeDataChain();
	m_pBlocks = NULL;
}

template <class KEY, class VALUE, template<class> class HASHKEY>
void HS_Hash<KEY, VALUE, HASHKEY, false>::RemoveBuckets()
{
	if (m_pHashTable != NULL)
	{
		delete [] m_pHashTable;
		m_pHashTable = NULL;
	}

	m_nCount = 0;
	m_pFreeList = NULL;
	m_pBlocks->FreeDataChain();
	m_pBlocks = NULL;
}

// iterating all (key, value) pairs
template <class KEY, class VALUE, template<class> class HASHKEY>
HS_POSITION HS_Hash<KEY, VALUE, HASHKEY, false>::GetStartPosition() const
{
	return (m_nCount == 0) ? NULL : HS_BEFORE_START_POSITION; 	
}

template <class KEY, class VALUE, template<class> class HASHKEY>
VALUE& HS_Hash<KEY, VALUE, HASHKEY, false>::operator[](KEY key)
{
	unsigned int nHash;
	CAssoc* pAssoc;
	if ((pAssoc = GetAssocAt(key, nHash)) == NULL)
	{
		if (m_pHashTable == NULL)
			InitHashTable(m_nHashTableSize);
		
		// it doesn't exist, add a new Association
		pAssoc = NewAssoc();
		
		assert(pAssoc!= NULL);
		
		pAssoc->nHashValue = nHash;
		KeyCopy(pAssoc->key, key);
		// 'pAssoc->value' is a constructed object, nothing more
		
		// put into hash table
		pAssoc->pNext = m_pHashTable[nHash];
		m_pHashTable[nHash] = pAssoc;
	}
	return pAssoc->value;  // return new reference
}

// remove key - return true if removed
template <class KEY, class VALUE, template<class> class HASHKEY>
bool HS_Hash<KEY, VALUE, HASHKEY, false>::RemoveKey(KEY key)
{
	if (m_pHashTable == NULL)
		return false;  // nothing in the table
	
	CAssoc** ppAssocPrev;
	ppAssocPrev = &m_pHashTable[ KeyHash(key, m_nHashTableSize) ];
	
	CAssoc* pAssoc;
	for (pAssoc = *ppAssocPrev; pAssoc != NULL; pAssoc = pAssoc->pNext)
	{
		//if (KeyCompare(&pAssoc->key, &key))
		if (KeyCompare(pAssoc->key, key))
		{
			// remove it
			*ppAssocPrev = pAssoc->pNext;  // remove from list
			FreeAssoc(pAssoc);
			return true;
		}
		ppAssocPrev = &pAssoc->pNext;
	}
	return false;  // not found
}

template <class KEY, class VALUE, template<class> class HASHKEY>
void HS_Hash<KEY, VALUE, HASHKEY, false>::GetNextAssoc(HS_POSITION& rNextPosition,
									   KEY& rKey, VALUE& rValue) const
{
	assert(m_pHashTable != NULL);  // never call on empty map
	
	CAssoc* pAssocRet = (CAssoc*)rNextPosition;
	assert(pAssocRet != NULL);
	
	if (pAssocRet == (CAssoc*) HS_BEFORE_START_POSITION)
	{
		// find the first association
		for (unsigned int nBucket = 0; nBucket < (unsigned int)m_nHashTableSize; nBucket++)
		{
			if ((pAssocRet = m_pHashTable[nBucket]) != NULL)
				break;
		}
		assert(pAssocRet != NULL);  // must find something
	}
	
	// find next association
	CAssoc* pAssocNext;
	if ((pAssocNext = pAssocRet->pNext) == NULL)
	{
		// go to next bucket
		for (unsigned int nBucket = pAssocRet->nHashValue + 1; nBucket < (unsigned int)m_nHashTableSize; nBucket++)
		{
			if ((pAssocNext = m_pHashTable[nBucket]) != NULL)
				break;
		}
	}
	
	rNextPosition = (HS_POSITION) pAssocNext;
	
	// fill in return data
	rKey = pAssocRet->key;
	rValue = pAssocRet->value;
}

// find association (or return NULL)
template <class KEY, class VALUE, template<class> class HASHKEY>
typename HS_Hash<KEY, VALUE, HASHKEY, false>::CAssoc* 
HS_Hash<KEY, VALUE, HASHKEY, false>::GetAssocAt(KEY key, unsigned int& nHash)const
{
	nHash = KeyHash(key, m_nHashTableSize);
	
	if (m_pHashTable == NULL)
		return NULL;
	
	// see if it exists
	CAssoc* pAssoc;
	for (pAssoc = m_pHashTable[nHash]; pAssoc != NULL; pAssoc = pAssoc->pNext)
	{
		if (KeyCompare(pAssoc->key, key))
			//if (pAssoc->key ==  key )
			return pAssoc;
	}
	return NULL;
}

template <class KEY, class VALUE, template<class> class HASHKEY>
void HS_Hash<KEY, VALUE, HASHKEY, false>::FreeAssoc(typename HS_Hash::CAssoc* pAssoc)
{
	KeyDelete(pAssoc->key);
	
	pAssoc->pNext = m_pFreeList;
	m_pFreeList = pAssoc;
	m_nCount--;
	assert(m_nCount >= 0);  // make sure we don't underflow
	
	// if no more elements, cleanup completely
	if (m_nCount == 0)
		RemoveBuckets();
}

template <class KEY, class VALUE, template<class> class HASHKEY>
typename HS_Hash<KEY, VALUE, HASHKEY, false>::CAssoc*
HS_Hash<KEY, VALUE, HASHKEY, false>::NewAssoc()
{
	if (m_pFreeList == NULL)
	{
		// add another block
		HS_CPlex* newBlock = HS_CPlex::Create(m_pBlocks, m_nBlockSize, sizeof(HS_Hash::CAssoc));
		// chain them into free list
		HS_Hash::CAssoc* pAssoc = (HS_Hash::CAssoc*) newBlock->data();
		// free in reverse order to make it easier to debug
		pAssoc += m_nBlockSize - 1;
		for (int i = m_nBlockSize-1; i >= 0; i--, pAssoc--)
		{
			pAssoc->pNext = m_pFreeList;
			m_pFreeList = pAssoc;
		}
	}
	assert(m_pFreeList != NULL);  // we must have something
	
	HS_Hash::CAssoc* pAssoc = m_pFreeList;
	m_pFreeList = m_pFreeList->pNext;
	m_nCount++;
	assert(m_nCount > 0);  // make sure we don't overflow

	//pAssoc->key = NULL;
	//pAssoc->value = NULL;	
	return pAssoc;
}

/// 如下定义正确，表示以char*为KEY，并忽略char*的大小写敏感特性
/// typedef HS_Hash<char*, unsigned long, HS_HashNoCaseStrKey> HS_MapStrToDWORD;  // OK
/// 如下定义错误，暂时没有具现 HS_MapNStrToDWORD<HSUINT16*>
/// typedef HS_Hash<HSUINT16*, unsigned long, HS_HashNoCaseStrKey> HS_MapNStrToDWORD; // ERROR

typedef HS_Hash<char*, unsigned long> HS_MapStrToDWORD;
typedef HS_Hash<HSUINT16*, unsigned long> HS_MapNStrToDWORD;
typedef HS_Hash<char*, void*> HS_MapStrToPtr;
typedef HS_Hash<HSUINT16*, void*> HS_NMapStrToPtr;

#endif
