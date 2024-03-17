#include <tinykit/TinyCharDriver.h>

void
TinyCharDriver::Process(
    message& rMsg,
    int ipcStatus
)
{
    int result = NONE;

    if(is_ipc_notify(ipcStatus))
    {
        /* TODO */
        return;
    }

    switch(rMsg.m_type)
    {
    case CDEV_OPEN:
        result = OpenOperatioon(rMsg);
        break;
    case CDEV_CLOSE:
        break;
    case CDEV_READ:
        break;
    case CDEV_WRITE:
        break;
    case CDEV_IOCTL:
        break;
    case CDEV_CANCEL:
        break;
    case CDEV_SELECT:
        break;
    default:
        Other(rMsg, ipcStatus);
    }
}

void
TinyCharDriver::Reply(
    message& msg,
    int ipcStatus,
    int result
)
{
    message reply;

    if(result == EDONTREPLY)
    {
        switch(msg.m_type)
        {
        case CDEV_READ:
        case CDEV_WRITE:
        case CDEV_IOCTL:
        case CDEV_CANCEL:
            break;
        default:
            fprintf(stderr, "TinyCharDriver wrong request %d\n", msg.m_type);
        }
    }
    else if(result == SUSPEND)
    {
        fprintf(stderr, "Suspend Not Used\n");
    }
    else if(result == ERESTART)
    {
        memset(&reply, 0, sizeof(reply));

        switch(msg.m_type)
        {
        case CDEV_OPEN:
        case CDEV_CLOSE:
            reply.m_type = CDEV_REPLY;
            reply.m_lchardriver_vfs_reply.status = result;
            reply.m_lchardriver_vfs_reply.id = msg.m_vfs_lchardriver_openclose.id;
            break;
        
        case CDEV_READ:
        case CDEV_WRITE:
        case CDEV_IOCTL:
            reply.m_type = CDEV_REPLY;
            reply.m_lchardriver_vfs_reply.status = result;
            reply.m_lchardriver_vfs_reply.id = msg.m_vfs_lchardriver_readwrite.id;
            break;

        case CDEV_CANCEL:
            reply.m_type = CDEV_REPLY;
            reply.m_lchardriver_vfs_reply.status = result;
            reply.m_lchardriver_vfs_reply.id = msg.m_vfs_lchardriver_cancel.id;
            break;

        case CDEV_SELECT:
            reply.m_type = CDEV_SEL1_REPLY;
            reply.m_lchardriver_vfs_sel1.status = result;
            reply.m_lchardriver_vfs_sel1.minor = msg.m_vfs_lchardriver_select.minor;
            break;

        default:
            fprintf(stderr, "Wrong Request Type: %d\n", msg.m_type);
        }
    }

    SendReply(msg.m_source, reply, ipcStatus);
}

void
TinyCharDriver::SendReply(
    endpoint_t endpt,
    message& msg,
    int ipcStatus
)
{
    int result = NONE;
    if(IPC_STATUS_CALL(ipcStatus) == SENDREC)
    {
        result = ipc_sendnb(endpt, &msg);
    }
    else
    {
        asynsend3(endpt, &msg, AMF_NOREPLY);
    }

    if(result != OK)
    {
        fprintf(stderr, "TinyCharDriver: Unable to send reply to %d: %d", endpt, result);
    }
}

int
TinyCharDriver::OpenOperatioon(
    message& msg
)
{
    int result;

    devminor_t minor;
    int access;
    endpoint_t user;

    minor = msg.m_vfs_lchardriver_openclose.minor;
    access = msg.m_vfs_lchardriver_openclose.access;
    user = msg.m_vfs_lchardriver_openclose.user;

    result = Open(
        minor,
        access,
        user
    );

    return result;
}

int
TinyCharDriver::CloseOperation(
    message& msg
)
{
    int result = NONE;

    return result;
}

int
TinyCharDriver::ReadOperation(
    message& message
)
{
    int result = NONE;

    return result;
}

void
TinyCharDriver::Start()
{
    /* TODO */

    int result;
    int ipcStatus;

    message msg;

    _running = true;

    while(_running)
    {
        result = sef_receive_status(
            ANY,
            &msg,
            &ipcStatus
        ); 
        if(result != OK)
        {
            if((result == EINTR) && 
                (!_running))
            {
                break;
            }

            fprintf(stderr, "Failed to receive [%d]\r\n", ipcStatus);
        }
        else
        {
            Process(
                msg,
                ipcStatus
            );
        }
    }
}