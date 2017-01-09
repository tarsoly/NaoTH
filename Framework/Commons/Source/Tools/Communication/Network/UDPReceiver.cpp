/**
 * @file UDPReceiver.cpp
 * @author <a href="mailto:xu@informatik.hu-berlin.de">Xu, Yuan</a>
 *
 */

#include "UDPReceiver.h"
#include "Tools/Debug/NaoTHAssert.h"

using namespace naoth;

void* UDPReceiver_static_loop(void* b)
{
  UDPReceiver* bl = static_cast<UDPReceiver*> (b);
  bl->loop();
  return NULL;
}

UDPReceiver::UDPReceiver(unsigned int port, unsigned int buffersize)
  : exiting(false), socket(NULL),
    socketThread(NULL)
{
  bufferSize = buffersize;
  buffer = new char[buffersize];

  if (!g_thread_supported()) {
    g_thread_init(NULL);
  }

  GError* err = bindAndListen(port);

  if(err)
  {
    g_warning("could not initialize TeamCommSocket properly: %s", err->message);
    g_error_free(err);
    return;
  }

  g_message("BroadCastLister start thread (%d)", port);
  socketThread = g_thread_create(UDPReceiver_static_loop, this, true, NULL);
  ASSERT(socketThread != NULL);
  g_thread_set_priority(socketThread, G_THREAD_PRIORITY_LOW);
}

UDPReceiver::~UDPReceiver()
{
  exiting = true;

  if ( socketThread )
  {
    g_thread_join(socketThread);
  }

  if(socket != NULL)
  {
    g_object_unref(socket);
  }

  delete [] buffer;
}

GError* UDPReceiver::bindAndListen(unsigned int port)
{
  GError* err = NULL;
  socket = g_socket_new(G_SOCKET_FAMILY_IPV4, G_SOCKET_TYPE_DATAGRAM, G_SOCKET_PROTOCOL_UDP, &err);
  if (err) return err;

  g_socket_set_blocking(socket, true);

  GInetAddress* inetAddress = g_inet_address_new_any(G_SOCKET_FAMILY_IPV4);
  GSocketAddress* socketAddress = g_inet_socket_address_new(inetAddress, static_cast<unsigned short>(port));

  g_socket_bind(socket, socketAddress, true, &err);

  g_object_unref(inetAddress);
  g_object_unref(socketAddress);

  return err;
}

void UDPReceiver::receive(std::vector<std::string>& data)
{
  data.clear();
  std::unique_lock<std::mutex> lock(messageInMutex, std::try_to_lock);
  if ( lock.owns_lock())
  {
    if ( !messageIn.empty() )
    {
      data = messageIn;
      messageIn.clear();
    }
  }
}

void UDPReceiver::loop()
{
  if(socket == NULL) {
    return;
  }

  while(!exiting)
  {
    gssize result = g_socket_receive(socket, buffer,
                                     bufferSize, NULL, NULL);
    if(result > 0)
    {
      std::lock_guard<std::mutex> lock(messageInMutex);
      messageIn.push_back(std::string(buffer, result));
    }
  }
}
