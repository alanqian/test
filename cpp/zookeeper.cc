
void zoo_watcher(zhandle_t *zh, int type, int state, const char *path, void* context )
{
    struct Stat stat;
    char        value[1024];
    int         valuelen = 1024;
    const char* mastername = BlockNode::instance()->getBlockNodeConf().getConfStr("zkPathMaster");
    MasterInfo  masterInfo;

    LOG4CXX_DEBUG(logger, format("got zookeeper notify"));
    int rc = zoo_exists(zh, mastername, 1, &stat);
    if (rc == ZOK)
    {
        rc = zoo_get(zh, mastername, 1, value, &valuelen, &stat);
        if ((ZOK == rc) && (0 != valuelen))
        {
            parseMasterInfo(value, masterInfo);
            masterChanged(&masterInfo);
            LOG4CXX_DEBUG(logger, format("master node changed success"));
        }
    }
    else
    {
        masterChanged(NULL);
    }
}

int zoo_init()
{
    const char* zkcluster = "cluster";
    int         zktimeout = 0; // ???
    const char* mastername = "master"; 

    _zh = zookeeper_init(zkcluster, zoo_watcher, zktimeout, 0, 0, 0 );
    if (_zh == NULL)
    {
        LOG4CXX_FATAL(logger, "zookeeper_init error");
        return -1;
    }

    blockNodePath = string(_conf.getConfStr("zkPathBlockNode")) + "/" + nodeSign;

    int ret = zoo_create(_zh, blockNodePath.c_str(), nodeSign.c_str(),
            strlen(nodeSign.c_str())+1,&ZOO_OPEN_ACL_UNSAFE, ZOO_EPHEMERAL,
            path_buffer, sizeof(path_buffer));
    if (ret != ZOK)
    {
        LOG4CXX_FATAL(logger, format("create path error,path:%s") % blockNodePath);
        return -1;
    }

    LOG4CXX_INFO(logger, format("zookeeper node create ok,path:%s") % path_buffer);

    struct Stat stat;
    char value[1024];
    int valuelen = 1024;

    int rc = zoo_exists(_zh, mastername, 1, &stat);
    if (rc == ZOK)
    {
        MasterInfo  masterInfo;

        rc = zoo_get(_zh, mastername, 1, value, &valuelen, &stat);
        if (rc != ZOK)
        {
            LOG4CXX_INFO(logger, format("zookeeper node get master failure:%s") % mastername);
            return -1;
        }
        parseMasterInfo(value, masterInfo);
        LOG4CXX_INFO(logger, format("zookeeper node get master:%s") % string(value));
        masterChanged(&masterInfo);
    }
    else
    {
        LOG4CXX_INFO(logger, format("master does not exist"));
    }

    return 0;
}

