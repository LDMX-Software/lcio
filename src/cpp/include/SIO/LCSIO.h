#ifndef SIO_LCSIO_H
#define SIO_LCSIO_H 1

#include "LCIOTypes.h"

#include "SIO_record.h" 
#include "SIO_definitions.h"

#include <string>

// record and block names used in LCIO-SIO
#define LCSIO_RUNRECORDNAME    "LCRunHeader"
#define LCSIO_RUNBLOCKNAME     "RunHeader"
#define LCSIO_EVENTRECORDNAME  "LCEvent"
#define LCSIO_EVENTBLOCKNAME   "Event"
#define LCSIO_HEADERRECORDNAME "LCEventHeader"
#define LCSIO_HEADERBLOCKNAME  "EventHeader"

#define LCSIO_ACCESSRECORDNAME "LCIORandomAccess"
#define LCSIO_ACCESSBLOCKNAME  "LCIORandomAccess"
#define LCSIO_RANDOMACCESS_SIZE 136 
#define LCSIO_INDEXRECORDNAME "LCIOIndex"
#define LCSIO_INDEXBLOCKNAME  "LCIOIndex"


class SIO_stream ;

namespace SIO {

  class LCSIO ;

  /** Manager class that holds instances of all known LCIO-SIO records.
   *  Provides Unpack class for setting subsets of records to be unpacked.
   *  Every new record type needs to be added here in SIORecords::ID and 
   *  SIORecords::Unpack.
   */
  class SIORecords {

    friend class LCSIO ;
  public:
    
    enum ID{
      Event=0,
      Header,
      Run,
      Access,
      Index,
      NumberOfRecords 
    } ;
    //-----------------------------------------------
    /** Helper class that sets the unpack flag of known SIO records
     *  as specified by the constructor. After an object of this class goes out of 
     *  scope the original setting is restored. This is needed to have multiple
     *  read streams (event overlay).
     */
    class Unpack{
    public:
      static const unsigned Event  = 0x0001 << SIORecords::Event ;
      static const unsigned Header = 0x0001 << SIORecords::Header ;
      static const unsigned Run    = 0x0001 << SIORecords::Run ;
      static const unsigned Access = 0x0001 << SIORecords::Access ;
      static const unsigned Index  = 0x0001 << SIORecords::Index ;

      static const unsigned All = 0xFFFFFFFF ; 
      
      Unpack( unsigned recordFlag ) ;
      ~Unpack() ;

    protected:
      bool _flags[ NumberOfRecords ] ;  
    };
    //-----------------------------------------------


    SIO_record* operator[](size_t idx) ;

    void setCompress( bool flag=true ) ;

  protected:
    void add(SIO_record*& rec, const char* name) ;

    SIO_record* _records[ NumberOfRecords ] ;

    SIORecords() ;
  } ;


#define LCSIO_READ( rec, pnt ) status = LCSIO::read( (rec), (pnt)  ); if( !(status & 1) ) return status;
#define LCSIO_READ_LEN( rec, pnt , len ) status = LCSIO::read( (rec), (pnt) , (len)  ); if( !(status & 1) ) return status;

#define LCSIO_WRITE( rec, pnt ) status = LCSIO::write( (rec), (pnt)  ); if( !(status & 1) ) return status;

/** Collection of static helper  functions for reading and writing
 * data with SIO. Could go to the SIO_functions class.
 * Also defines some constant names for lcio-SIO.
 *
 * @author gaede
 * @version Mar 6, 2003
 */
  class LCSIO{
  
  public :
  
    static SIORecords& records() ;

//     // define some names of records and blocks
//     static const char* RUNRECORDNAME ; 
//     static const char* RUNBLOCKNAME ; 
//     static const char* EVENTRECORDNAME ; 
//     static const char* EVENTBLOCKNAME;
//     static const char* HEADERRECORDNAME ; 
//     static const char* HEADERBLOCKNAME;

     static const char* FILE_EXTENSION ;

    /** the compression mode for SIO
     */
    static const bool COMPRESSION = true ;


    /**Checks the version of the file - oldefile (version < v00-08) are no longer supported
     * 
     * @throws IOException if the version is not supported
     */
    static void checkVersion(int versionID ) ;

    /** Read a string from the stream into a dummy buffer. 
     * Warning the same buffer is used for each call.
     * So the return value needs to be copied to its final memory destination.
     * len holds the length of the string (can contain '\0').
     */
    static unsigned int read( SIO_stream* stream ,char** c , int* len=0) ;

//     /** This version checks the versionId to be able to read 'old' files with 
//      * trailing '\00' (version <= 00-02).
//      * Remove this method after a reasonable transition period...
//      */
//     static unsigned int read( SIO_stream* stream ,char** c, int versionID) ;
  
    /** Write an int to the stream.
     */
    static unsigned int write( SIO_stream* stream , int i) ;

    /** Write an unsigned int to the stream.
     */
    static unsigned int write( SIO_stream* stream , unsigned int i) ;
  
    /** Write a vector size to the stream (needed for AMD64 architectures)
     */
#if defined(_LP64)  || defined(__APPLE_CC__)
//    static unsigned int write( SIO_stream* stream , SIO_POINTER_DECL i) ;
    static unsigned int write( SIO_stream* stream , size_t i) ;
#endif

    /** Write a 64bit integer to the stream 
     */
    static unsigned int write( SIO_stream* stream , EVENT::long64 i) ;

    /** Write a float  to the stream.
     */
    static unsigned int write( SIO_stream* stream , float f) ;
  
    /** Write a string to the stream. Writes 
     * the length of the string first and adds '\0' to the end.
     */
    static unsigned int write(SIO_stream* stream , const std::string& s) ;
  
  
    /** Creates a valid SIO name (basically equivalent to a valid C++ name)
     * by replacing every [.], [\] and [/] with underscores and removing all
     * nonalphanumeric characters and adding an 'A' to the beginning, if necessary.
     */
    static std::string getValidSIOName(const std::string& aName ) ;
    //    static const char* getValidSIOName(const std::string& aName ) ;


    /**Seek stream to the given absolute position - if pos<0 from end of file.
     * Throws IOException if stream is not open or seek fails.
     * 
     * @throw IOException
     */
    static void seekStream( SIO_stream* stream , EVENT::long64 pos) ;


  private:

    static char* dummy  ;
    static int dummy_size  ;
    static int uid ;
    static const int dummy_initial_size = 1024  ;

  } ;

} // namespace 
#endif // ifndef SIO_LCSIO_H
