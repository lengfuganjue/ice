// **********************************************************************
//
// Copyright (c) 2003-2007 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package IceInternal;

public class LocalExceptionWrapper extends Exception
{
    public
    LocalExceptionWrapper(Ice.LocalException ex, boolean retry)
    {
        _ex = ex;
        _retry = retry;
    }

    public
    LocalExceptionWrapper(IceInternal.LocalExceptionWrapper ex)
    {
        _ex = ex.get();
        _retry = ex._retry;
    }

    public Ice.LocalException
    get()
    {
        return _ex;
    }

    //
    // If true, always repeat the request. Don't take retry settings
    // or "at-most-once" guarantees into account.
    //
    // If false, only repeat the request if the retry settings allow
    // to do so, and if "at-most-once" does not need to be guaranteed.
    //
    public boolean
    retry()
    {
        return _retry;
    }

    public static void
    throwUnknownWrapper(java.lang.Throwable ex) throws LocalExceptionWrapper
    {
        if(ex instanceof Ice.UserException)
        {
            throw new LocalExceptionWrapper(new Ice.UnknownUserException(((Ice.UserException)ex).ice_name()), false);
        }
        if(ex instanceof Ice.LocalException)
        {
            /*
            //
            // Commented-out code makes local exceptions fully location transparent,
            // but the Freeze evictor relies on them not being transparent.
            //
            if(ex instanceof Ice.UnknownException ||
               ex instanceof Ice.ObjectNotExistException ||
               ex instanceof Ice.OperationNotExistException ||
               ex instanceof Ice.FacetNotExistException)
            {
                throw new LocalExceptionWrapper((Ice.LocalException)ex, false);
            }
            throw new LocalExceptionWrapper(new Ice.UnknownLocalException(ex.ice_name()), false);
            */
            throw new LocalExceptionWrapper((Ice.LocalException)ex, false);
        }
        /*
        throw new LocalExceptionWrapper(new Ice.UnknownException(ex.toString()), false);
        */

        if(ex instanceof RuntimeException)
        {
            throw (RuntimeException)ex;
        }
    }

    private Ice.LocalException _ex;
    private boolean _retry;
}
