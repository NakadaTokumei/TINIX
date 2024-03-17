#include <cstdio>

#include <testtiny.h>
#include <tinykit/TinyCharDriver.h>

class TestTinyChardriver : public TinyCharDriver
{
protected:
    virtual int
    Open(
        devminor_t UNUSED(minor),
        int UNUSED(access),
        endpoint_t UNUSED(userEndpt)
    ) override;

    virtual int
    Close(
        devminor_t UNUSED(minor)
    ) override;

    virtual ssize_t
    Read(
        devminor_t UNUSED(minor),
        u64_t UNUSED(pos),
        endpoint_t UNUSED(endpt),
        cp_grant_id_t UNUSED(grant),
        size_t UNUSED(size),
        int UNUSED(flags),
        TinyCharDevID UNUSED(id)
    ) override;
public:
    virtual void
    Start(void) override;
};

int 
TestTinyChardriver::Open(
    devminor_t UNUSED(minor),
    int UNUSED(access),
    endpoint_t UNUSED(userEndpt)
)
{
    printf("[TestTinykit] Driver Open!!\n");
    return OK;
}

int 
TestTinyChardriver::Close(
    devminor_t UNUSED(minor)
)
{
    printf("[TestTinykit] Driver Close!!\n");
    return OK;
}

ssize_t
TestTinyChardriver::Read(
    devminor_t UNUSED(minor),
    u64_t UNUSED(pos),
    endpoint_t UNUSED(endpt),
    cp_grant_id_t UNUSED(grant),
    size_t UNUSED(size),
    int UNUSED(flags),
    TinyCharDevID UNUSED(id)
)
{
    printf("[TestTinykit] Driver Read\n");

    return size;
}

void
TestTinyChardriver::Start(void)
{
    TinyCharDriver::Start();
}

int main(void)
{
    TinyCharDriver chardriver;

    // Process of TinyCharDriver
    chardriver.Start();
}