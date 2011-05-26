#ifndef PROPERTY_H
#define PROPERTY_H

#define PROP_ARG( type, val )     private: type val;
#define PROP_SET( type, val, set )  public: void set( type x ){ val = x; }
#define PROP_GET( type, val, get )  public: const type get() const { return( val ); }

#define PROPERTY( type, val, set, get ) \
        PROP_ARG( type, val )\
        PROP_SET( type, val, set )\
        PROP_GET( type, val, get )

#endif // PROPERTY_H
