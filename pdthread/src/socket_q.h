#ifndef __libthread_socket_q_h__
#define __libthread_socket_q_h__

#ifndef __in_thrtabentries__
#error You should not include this file directly
#endif

#include "../h/thread.h"
#include "hashtbl.C"


namespace pdthr
{

class socket_q : public io_entity {
  private:
    static hashtbl<PdSocket,socket_q*> socket_registry;    
  public:
    socket_q( PdSocket the_sock, thread_t owned_by,
             int (*will_block_func)(void*), void* desc,
			 bool is_special=false);

    virtual ~socket_q();
    
    virtual item_t gettype() { return item_t_socket; }
    static socket_q* socket_from_desc( const PdSocket& fd );
    PdSocket sock;

    virtual int do_read(void* buf, unsigned bufsize, unsigned* count);
    virtual int do_write(void* buf, unsigned bufsize, unsigned* count);
}; /* end of class socket_q */

} // namespace pdthr

#endif
