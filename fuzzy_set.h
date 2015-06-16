#ifndef FUZZY_SET_H
#define FUZZY_SET_H

/* Class that represents a trapezoidal fuzzy set.
 *
 * The set's function's graph is
 *          ___________
 *         /.         .\
 *        / .         . \
 *       /  .         .  \
 *      /   .         .   \
 * ____/____._________.____\_____
 *     le  lm         rm   re
 *
 * le, lm, rm and re, are, respectively,
 * left extremum, left middle, right middle, and right extremum.
 * We assume le <= lm <= rm <= re,
 * but some of these values might be equal to each other.
 *
 * Any value outside the range [le, re] will receive pertinence value 0.0.
 * Any value inside the range (lm, rm) will receive pertinence value 1.0.
 * Values in [le, lm] and [rm, re] will have linearly interpolated pertinence values.
 * If the distance between le and lm (or rm and re)
 * is smaller than the machine epsilon,
 * then any number in that interval will receive pertinence value 0.5.
 */

class FuzzySet {
    double le, lm, rm, re;
public:
    FuzzySet( double, double, double, double );

    /* Returns how much the given number belong to this fuzzy set.
     */
    double pertinence( double ) const;
    double operator()( double d ) const {
        return pertinence( d );
    }
};

#endif // FUZZY_SET_H
