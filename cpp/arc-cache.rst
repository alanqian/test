Summary
-------

Basic LRU maintains an ordered list (the cache directory) of resource
entries in the cache, with the sort order based on the time of most recent
access. New entries are added at the top of the list, after the bottom
entry has been evicted. Cache hits move to the top, pushing all other
entries down.

ARC improves the basic LRU strategy by splitting the cache directory into
two lists, T1 and T2, for recently and frequently referenced entries. In
turn, each of these is extended with a ghost list (B1 or B2), which is
attached to the bottom of the two lists. These ghost lists act as
scorecards by keeping track of the history of recently evicted cache
entries, and the algorithm uses ghost hits to adapt to recent change in
resource usage. Note that the ghost lists only contain metadata (keys for
the entries) and not the resource data itself, i.e. as an entry is evicted
into a ghost list its data is discarded. 

The combined cache directory is organised in four LRU lists:

    T1, for recent cache entries.
    T2, for frequent entries, referenced at least twice.
    B1, ghost entries recently evicted from the T1 cache, but are still tracked.
    B2, similar ghost entries, but evicted from T2.

T1 and B1 together are referred to as L1, a combined history of recent
single references. Similarly, L2 is the combination of T2 and B2.

The whole cache directory can be visualised in a single line:

. . . [   B1  <-[     T1    <-!->      T2   ]->  B2   ] . .
      [ . . . . [ . . . . . . ! . .^. . . . ] . . . . ]
                [   fixed cache size (c)    ]

The inner [ ] brackets indicate actual cache, which although fixed in size, can
move freely across the B1 and B2 history.

L1 is now displayed from right to left, starting at the top, indicated by the !
marker. ^ indicates the target size for T1, and may be equal to, smaller than,
or larger than the actual size (as indicated by !).

    New entries enter T1, to the left of !, and are gradually pushed to the
left, eventually being evicted from T1 into B1, and finally dropped out
altogether.

    Any entry in L1 that gets referenced once more, gets another chance, and
enters L2, just to the right of the central ! marker. From there, it is again
pushed outward, from T2 into B2. Entries in L2 that get another hit can repeat
this indefinitely, until they finally drop out on the far right of B2.

Replacement
-----------

Entries (re-)entering the cache (T1,T2) will cause ! to move towards the target
marker ^. If no free space exists in the cache, this marker also determines
whether either T1 or T2 will evict an entry.

    Hits in B1 will increase the size of T1, pushing ^ to the right. The last
entry in T2 is evicted into B2.

    Hits in B2 will shrink T1, pushing ^ back to the left. The last entry in T1
is now evicted into B1.

    A cache miss will not affect ^, but the ! boundary will move closer to ^.

    insert:
        new entry: to tail of T1;
        hit(T1):   to tail of T2;

    if hit(T2): move the hit object to tail of T2;
    if hit(T1): move hit object from T1 to T2;
    if hit(B1): resize T1 by +1; resize T2 by -1; evict(last(B2));
    if hit(B2): resize T1 by -1; resize T2 by +1; evict(last(B1));
    if no hit:  if size(T1) > size(T2): evict(last(B1));
                if size(T2) > size(T1): evict(last(B2));

