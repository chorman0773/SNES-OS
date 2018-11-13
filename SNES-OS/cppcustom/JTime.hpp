#ifndef __JTime_hpp_2018_05_16_08_23
#define __JTime_hpp_2018_05_16_08_23
#include <stdint.h>
#include "../../SNES-OS/cppcustom/Hash.hpp"

enum class ChronoUnit{
    NANOSECONDS, MICROSECONDS, MILISECONDS, SECONDS,
    MINUTES, HOURS
};



class Duration;
class Instant;

/*
    Represents an Instant in time.
    Each Instant is precise to Nanoseconds, but may not be accurate to Nanoseconds.
    Instant's can be aquired using any of the Factory methods, including the "now()" Method with obtains an Instant from the system clock.
    Instant's are not time zone sensitive and resolve to UTC timer.
    The Instant class is effectively Immutable. All Methods are const qualified and return a unqiue instance instead of modifying the object, if they would change fields.
    The Instant class tracks signed 64-bit integer for seconds and 32-bit nanoseconds. (0-999999999)
    This represents a time since the Unix EPOCH, or 1970-01-01T00:00:00.000000000Z (January 1st, 1970, at 12:00:00 exactly, UTC)
*/
class Instant :public Hashable{
private:
    int64_t seconds;
    int nanos;
    Instant(int64_t,int);
public:
    /*
        Constructs an instant with both fields set to zero. Effectively the same as Copy-Constructing with the EPOCH constant.
    */
    Instant();
    /*
        Obtains an Instant from the current system clock. This method should attempt to produce the most accurate result possible.
        This factory method can produce Inaccurate Instants, depending on the accuracy of the system clock.
        The accuracy of the resultant instant is the lesser of the accuracy of the system clock and nanosecond accuracy.
    */
    static Instant now();
    /*
        Obtains an Instant based on a number of seconds since the Epoch, adjusted by a number of nanoseconds.
        seconds can be any 64-bit integer value, while nanoAdjustment must be between 0 (inclusive) and 1000000000 (exclusive).
        If nanoAdjustment is not within this range, then both it an the seconds field are adjusted proprotionally until the values
        are effectively equal, and nanoAdjustment is within the specified range. For example the following will produce the exact same Instant:
        Instant::fromEpochSecond(3,1);
        Instant::fromEpochSecond(4,-999999999);
        Instant::fromEpochSecond(2,1000000001);.
    */
    static Instant fromEpochSecond(int64_t seconds,int nanoAdjustment);
    /*
        Obtains an instant based on a number of seconds since the Epoch.
        This factory method is effectively the same as the call Instant::fromEpochSecond(seconds,0)
    */
    static Instant fromEpochSecond(int64_t seconds);
    /*
        Obtains an instant based on a number of miliseconds since the epoch.
        This factory method is effecitvely the same as the call Instant::fromEpochSecond(miliseconds/1000,(miliseconds%1000000)*1000));
    */
    static Instant fromEpochMilisecond(int64_t miliseconds);
    /*
        Subtracts a given Duration from this instant.
        The resultant Instant is taken from this instant and offset by the inverse of the given duration, such that:
        for any Instant i and Duration d, Duration::between(i.subtract(d),i)==d.
        This method does not modify this Instant and returns a new instant that the above is true for.
    */
    Instant subtract(const Duration&) const;
    /*
        Adds a given Duration to this instant.
        The resultant Instant is taken from this instant and offset by the given duration, such that:
        for any Instant i and Duration d, Duration::between(i,i.add(d))==d.
        This method does not modify this Instant and returns a new Instant that the above is true for.
    */
    Instant add(const Duration&) const;
    /*
        Truncates this instant to the given unit.
        If this Instant is not accurate to or is exactly accurate to the given unit, the resultant Instant is identical to this one.
        Otherwise, the resultant Instant has its fields set so that it accurately represents this Instant, to that unit.
        Any information that makes the resultant instant more accurate then the given unit is lost, and results in 0.
        For any Instant i, i.truncateTo(ChronoUnit::NANOSECONDS)==i is true.
        The resultant Instant is guarenteed to be accurate to at most the given Unit.
    */
    Instant truncateTo(ChronoUnit)const;
    /*
        Checks if this Instant occurs before another in time.
    */
    bool isBefore(const Instant&)const;
    /*
        Checks if this Instant occurs after another in time.
    */
    bool isAfter(const Instant&)const;
    /*
        Compares this instant to another, based on its occurance in time.
        This comparison is guarenteed to be as accurate as the highest accuraccy between the 2 instants.
    */
    int compareTo(const Instant&)const;
    /*
        Compares this instant to another for equality.
        For any Instants i and j, i==j is effecitvely equivalent to i.compareTo(j)==0.
        2 instants are equal if they occur at the same point in time, precise to nanoseconds.
    */
    bool operator==(const Instant&)const;
    /*
        Compares this instant to another.
        For any Instants i and j, i<j is effectively equivalent to i.compareTo(j)<0.
        An instant is greater than another if it occurs before the other in time.
    */
    bool operator<(const Instant&)const;
    /*
        Compares this instant to another.
        For any Instants i and j, i<=j is effecitvely equivalent to i.compareTo(j)<=0.
        An instant is greater than another if it occurs before the other in time, or both occur at the same point in time.
    */
    bool operator<=(const Instant&)const;
    /*
        Compares this instant to another.
        For any Instants i and j, i>j is effecitvely equivalent to i.compareTo(j)>0.
        An instant is greater than another if it occurs after the other in time.
    */
    bool operator>(const Instant&)const;
    /*
        Compares this instant to another.
        For any Instants i and j, i>=j is effecitvely equivalent to i.compareTo(j)>=0.
        An instant is greater than another if it occurs after the other in time, or both occur at the same point in time.
    */
    bool operator>=(const Instant&)const;
    /*
        Compares this instant to another.
        For any Instants i and j, i!=j is effecitvely equivalent to i.compareTo(j)!=0.
        An instant is not-equal to another if they do not occur at the same point in time.
    */
    bool operator!=(const Instant&)const;
    /*
        Adds the given duration to this.
        For Any Instant i and Duration d, i+d is effectively equivalent to i.add(d) and result in the same Instant
    */
    Instant operator+(const Duration&)const;
    /*
        Subtracts a given duration from this.
        For any Instant i and Duration d, i-d is effectively equivalent to i.subtract(d) and result in the same Instant
    */
    Instant operator-(const Duration&)const;
    /*
        Gets the Number of seconds since the Epoch this Instant Describes.
    */
    int64_t toEpochSecond() const;
    /*
        Obtains the Nano field of this Instant, ranging from 0 inclusive to 1000000000 exclusive
    */
    int     getNanos() const;
    /*
        Obtains the value of this instant, as a number of the given ChronoUnit since the Epoch.
        The resulting value is equivlanent to the one produced from this instant, Truncated to that unit.
    */
    int64_t get(ChronoUnit)const;

    /*
        Gets the hashcode of the given Instant.
        This is computed from the hashcode of its seconds field and the hashcode of its nano's field.
    */
    int32_t hashCode()const;
};
/*
    Instant Constant Representing the Epoch (January 01, 1970 at 00:00:00 Exactly UTC)
*/
const Instant EPOCH = Instant::fromEpochSecond(0);
/*
    Instant Constant Holding the Effective Max value for an instant (1<<63-1 seconds, 999999999 nanoseconds)
*/
const Instant MAX = Instant::fromEpochSecond(9223372036854775807,999999999);
/*
    Instant Constant Holding the Effective Minimum value for an instant (-(1<<63) seconds)
*/
const Instant MIN = Instant::fromEpochSecond(-9223372036854775808);
/*
    A class that represents a Duration between 2 Instants.
    This Duration is precise to Nanoseconds and stores 64-bit seconds with 32-bit nanoseconds.
*/
class Duration:public Hashable{
private:
    int64_t seconds;
    int nanos;
    Duration(int64_t seconds,int nanoTime);
public:
    /*
        Returns the Duration that is between 2 Instants
    */
    static Duration between(const Instant&,const Instant&);
    /*
        Represents the given Instant as a Duration, specifically the one returned by
        between(EPOCH,i) for any instant i.
    */
    static Duration fromEpoch(const Instant&);
    /*
        Produces a duration by a given number of seconds, adjusted by the given nanoseconds.
        The values are adjusted to constrain the number of nanoseconds to between 0 inclusive and 100000000 exclusive,
        similarily to Instant.ofEpochSeconds(seconds,nanoAdjustment);.
    */
    static Duration ofSeconds(int64_t seconds,int nanoAdjustment);
    /*
        Produces a Duration by a given Number of seconds.
        The Time Elapsed by the Duration is exactly that many seconds
    */
    static Duration ofSeconds(int64_t seconds);
    /*
        Produces a duration by a given Number of a specific unit.
    */
    static Duration of(int64_t,ChronoUnit);
    /*
        Produces a new duration that equivalent to the given duration subtracted from this duration.
    */
    Duration subtract(const Duration&)const;
    /*
        Produces a new duration that is equivalent to the given duration added to this duration.
    */
    Duration add(const Duration&)const;
    /*
        Produces a new duration that is equivalent to this duration, with the given number of seconds added.
    */
    Duration addSeconds(int64_t seconds)const;
    /*
        Produces a new duration that is equivalent to this duration with the given number of miliseconds added.
    */
    Duration addMiliseconds(int64_t miliseconds)const;
    /*
        Produces a new duration that is equivalent to this duration with the given ammount of the specified unit added.
    */
    Duration add(int64_t,ChronoUnit)const;
    /*
        Gets the seconds field of this Instant.
    */
    int64_t getSeconds()const;
    /*
        Gets the nanoseconds field of this Instant.
    */
    int     getNanos()const;
    /*
        Produces a new duration that is equivalent to the negation of this duration.
        Negating The Minimum Duration will result in an out_of_bounds exception being thrown.
        For Any 2 Instants i and j, Duration::between(i,j).negate() is equal to Duration::between(j,i)
    */
    Duration negate()const;
    /*
        Comapres this duration with another.
        THis comparison will result in a negative value if this duration is less than the given duration,
        0 if this duration is the same as the given duration, and a positive value if this duration is greater than the other duration
    */
    int compareTo(const Duration&)const;
    /*
        Produces a new Duration, that is the absolute value of this Duration.
        If this duration is negative, then this is equivalent to negating this duration. Otherwise, it is equivalent to this duration.
        Taking the absolute value of the Minimum duration will result in an out_of_bounds exception being thrown.
    */
    Duration abs()const;
    /*
        Checks if this duration is negative.
        A Duration is negative if it is less than the Constant ZERO
    */
    bool isNegative()const;
    /*
        Truncates this Duration to a given chrono unit.
        This operation should be similar the same trucation with Instant
    */
    Duration truncateTo(ChronoUnit)const;
    /*
        Negates this Duration.
        Effectively the same as d.negate() for this duration d.
    */
    Duration operator-()const;
    /*
        Adds a Duration to this Duration.
        Effectively the same as the same call to add.
    */
    Duration operator+(const Duration&)const;
    /*
        Adds a Duration to this Duration.
        Effectively the same as the same call to add.
    */
    Duration operator-(const Duration&)const;
    /*
        Compares this duration to annother.
        For any Duration d and e, d==e is effectively equivalent to d.compareTo(e)==0
    */
    bool operator==(const Duration&)const;
    /*
        Compares this duration to annother.
        For any Duration d and e, d<e is effectively equivalent to d.compareTo(e)<0
    */
    bool operator<(const Duration&)const;
    /*
        Compares this duration to annother.
        For any Duration d and e, d>e is effectively equivalent to d.compareTo(e)>0
    */
    bool operator>(const Duration&)const;
    /*
        Compares this duration to annother.
        For any Duration d and e, d<=e is effectively equivalent to d.compareTo(e)<=0
    */
    bool operator<=(const Duration&)const;
    /*
        Compares this duration to annother.
        For any Duration d and e, d>=e is effectively equivalent to d.compareTo(e)>=0
    */
    bool operator>=(const Duration&)const;
    /*
        Compares this duration to annother.
        For any Duration d and e, d!=e is effectively equivalent to d.compareTo(e)!=0
    */
    bool operator!=(const Duration&)const;

    /*
        Computes the hashcode of this Instant.
        This hashcode is computed from the hashcode of its seconds field and its nanoseconds field
    */
    int hashCode()const;
};

const Duration ZERO = Duration::ofSeconds(0);
const Duration MAX_DURATION = Duration::ofSeconds(9223372036854775807,999999999);
const Duration MIN_DURATION = Duration::ofSeconds(-9223372036854775808);
#endif
