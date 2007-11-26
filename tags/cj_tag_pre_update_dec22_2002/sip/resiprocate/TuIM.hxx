#if !defined(UDPTRANSPORT_HXX)
#define UDPTRANSPORT_HXX

#include <vector>

#include "sip2/sipstack/Security.hxx"

namespace Vocal2
{

class TuIM
{
   public:

      class PageCallback
      {
         public:
            virtual void receivedPage(const Data& msg, const Uri& from, 
                                      const Data& signedBy,  Security::SignatureStatus sigStatus,
                                      bool wasEncryped  ) = 0; 
            virtual ~PageCallback();
      };
      
      class ErrCallback
      {
         public:
            virtual void sendPageFailed(const Uri& dest ) =0;
            virtual ~ErrCallback();
      };
      
      class PresCallback
      {
         public:
            virtual void presenseUpdate(const Uri& dest, bool open, const Data& status ) =0;
            virtual ~PresCallback();
      };
      
      TuIM(SipStack* stack, 
           const Uri& aor, 
           const Uri& contact,
           PageCallback* pageCallback, 
           ErrCallback* errCallback,
		   PresCallback* pressCallback);
      
      void sendPage(const Data& text, const Uri& dest, bool sign, const Data& encryptFor );

      void process();

	  // Registration management 
	  void registerAor( const Uri& uri, const Data& password = Data::Empty );

	  // Buddy List management
	  const int getNumBudies();
	  const Uri getBuddyUri(const int index);
	  const Data getBuddyGroup(const int index);
	  void addBuddy( const Uri& uri, const Data& group );
      void removeBudy( const Uri& name);

	  // Presense management
	  void setMyPresense( const bool open, const Data& status = Data::Empty );

   private:
      PageCallback* mPageCallback;
      ErrCallback* mErrCallback; 
	  PresCallback* mPressCallback;
      SipStack* mStack;
      Uri mAor;
      Uri mContact;
	  Data mPassword;

	  class Buddy
	  {
	  public:
		  Uri uri;
		  Data group;
	  };

	  vector<Buddy> mBuddy;
};

}

#endif


/* ====================================================================
 * The Vovida Software License, Version 1.0 
 */

