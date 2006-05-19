// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICEGRID_ADMINSESSIONI_H
#define ICEGRID_ADMINSESSIONI_H

#include <IceGrid/SessionI.h>
#include <IceGrid/Topics.h>

namespace IceGrid
{

class AdminSessionI : public BaseSessionI, public AdminSession
{
public:

    AdminSessionI(const std::string&, const DatabasePtr&, int, const RegistryObserverTopicPtr&, 
		  const NodeObserverTopicPtr&);
    virtual ~AdminSessionI();

    virtual AdminPrx getAdmin(const Ice::Current&) const;

    virtual void setObservers(const RegistryObserverPrx&, const NodeObserverPrx&, const Ice::Current&);
    virtual void setObserversByIdentity(const Ice::Identity&, const Ice::Identity&, const Ice::Current&); 

    virtual int startUpdate(const Ice::Current&);
    virtual void addApplication(const ApplicationDescriptor&, const Ice::Current&);
    virtual void syncApplication(const ApplicationDescriptor&, const Ice::Current&);
    virtual void updateApplication(const ApplicationUpdateDescriptor&, const Ice::Current&);
    virtual void removeApplication(const std::string&, const Ice::Current&);
    virtual void finishUpdate(const Ice::Current&);

    virtual void destroy(const Ice::Current&);

private:
    
    const RegistryObserverTopicPtr _registryObserverTopic;
    const NodeObserverTopicPtr _nodeObserverTopic;
    
    RegistryObserverPrx _registryObserver;
    NodeObserverPrx _nodeObserver;
    bool _updating;
};
typedef IceUtil::Handle<AdminSessionI> AdminSessionIPtr;

class AdminSessionManagerI : virtual public Glacier2::SessionManager
{
public:

    AdminSessionManagerI(const  DatabasePtr&, int, const RegistryObserverTopicPtr& , const NodeObserverTopicPtr&);
    
    virtual Glacier2::SessionPrx create(const std::string&, const Glacier2::SessionControlPrx&, const Ice::Current&);
    AdminSessionIPtr create(const std::string&);

private:
    
    const DatabasePtr _database;
    const int _timeout;
    const RegistryObserverTopicPtr _registryObserverTopic;
    const NodeObserverTopicPtr _nodeObserverTopic;
};
typedef IceUtil::Handle<AdminSessionManagerI> AdminSessionManagerIPtr;

};

#endif
