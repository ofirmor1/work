#ifndef CDR_HPP
#define CDR_HPP

typedef enum UsageType
{
    MOC //outgoing voice call
    MTC //incoming voice call
    SMS-MO //outgoing message
    SMS-MT //incoming message

    D //Data
    U //call not answered
    B //busy call
    X //failed call
}UsageType;



namespace cdr
{

}//namespace cdr
class Cdr
{
public:
    Cdr(/* args */);
    ~Cdr();

private:
    Sequence
    IMSI
    MEI
    sage Type
    SISDN
    Call date
    Call time
    Duration(sec)
    Bytes Rx
    Bytes Tx
    2nd Party IMSI
    2nd Party MSISDN
};




#endif /*#ifndef CDR_HPP*/