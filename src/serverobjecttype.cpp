/*
 * Copyright (C) 2017 -  B. J. Hill
 *
 * This file is part of open62541 C++ classes. open62541 C++ classes are free software: you can
 * redistribute it and/or modify it under the terms of the Mozilla Public
 * License v2.0 as stated in the LICENSE file provided with open62541.
 *
 * open62541 C++ classes are distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.
 */
#include "serverobjecttype.h"


/**
* Open62541::ServerObjectType::ServerObjectType
* @param n
*/
Open62541::ServerObjectType::ServerObjectType(Server &s, const std::string &n) : _server(s),  _name(n) {
}

/**
* ~ServerObjectType
*/
Open62541::ServerObjectType::~ServerObjectType() {

}

/**
* addBaseObjectType
* @param n
* @param typeId
* @return 
*/
bool Open62541::ServerObjectType::addBaseObjectType(const std::string &n,
                                                    NodeId &requestNodeId,
                                                    NodeContext *context) {
    ObjectTypeAttributes dtAttr;
    QualifiedName qn(_nameSpace, n);
    dtAttr.setDisplayName(n);
    _typeId.notNull();
    return _server.addObjectTypeNode(requestNodeId,
                                     NodeId::BaseObjectType,
                                     NodeId::HasSubType,
                                     qn,
                                     dtAttr,
                                     _typeId,context);
}


/**
* addDerivedObjectType
* @param n
* @param parent
* @param typeId
* @return 
*/
bool Open62541::ServerObjectType::addDerivedObjectType(const std::string &n,
                                                       NodeId &parent,
                                                       NodeId &typeId,
                                                       NodeId &requestNodeId ,
                                                       NodeContext *context) {
    ObjectTypeAttributes ptAttr;
    ptAttr.setDisplayName(n);
    QualifiedName qn(_nameSpace, n);
    //
    return _server.addObjectTypeNode(requestNodeId, parent, NodeId::HasSubType, qn,
                                     ptAttr, typeId,context);
}



/**
* add
* @param server
* @param baseId
* @return 
*/
bool Open62541::ServerObjectType::addType(NodeId &nodeId) { // base node of type
    if (addBaseObjectType(_name, nodeId)) {
        return addChildren(_typeId);
    }
    return false;
}

/**
* append
* @param server
* @param parent
* @param nodeId
* @return 
*/
bool Open62541::ServerObjectType::append(NodeId &parent, NodeId &nodeId, NodeId &requestNodeId) { // derived type - returns node id of append type
    if (addDerivedObjectType(_name, parent, nodeId, requestNodeId)) {
        return addChildren(nodeId);
    }
    return false;
}

/**
* Open62541::ServerObjectType::addInstance
* @param n
* @param parent
* @param nodeId
* @return 
*/
bool Open62541::ServerObjectType::addInstance(const std::string &n, NodeId &parent,
                                              NodeId &nodeId, NodeId &requestNodeId, NodeContext *context) {
   bool ret = _server.addInstance(n,
                               requestNodeId,
                               parent,
                               _typeId,
                               nodeId,
                               context);
   UAPRINTLASTERROR(_server.lastError());
   return ret;
}




