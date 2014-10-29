#ifndef __NODE_GDAL_DRIVER_H__
#define __NODE_GDAL_DRIVER_H__

// node
#include <node.h>
#include <node_object_wrap.h>

// nan
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <nan.h>
#pragma GCC diagnostic pop

// gdal
#include <gdal_priv.h>

// ogr
#include <ogrsf_frmts.h>

#include "obj_cache.hpp"

using namespace v8;
using namespace node;

// > GDAL 2.0 : a wrapper for GDALDriver
// < GDAL 2.0 : a wrapper for either a GDALDriver or OGRSFDriver that behaves like a 2.0 Driver
// 
namespace node_gdal {

class Driver: public node::ObjectWrap {
public:
	static Persistent<FunctionTemplate> constructor;
	static void Initialize(Handle<Object> target);
	static NAN_METHOD(New);
	static Handle<Value> New(GDALDriver *driver);
	static Handle<Value> New(OGRSFDriver *driver);
	static NAN_METHOD(toString);
	static NAN_METHOD(open);
	static NAN_METHOD(create);
	static NAN_METHOD(createCopy);
	static NAN_METHOD(deleteDataset);
	static NAN_METHOD(rename);
	static NAN_METHOD(copyFiles);
	static NAN_METHOD(getMetadata);

	static ObjectCache<GDALDriver>  cache;
	static ObjectCache<OGRSFDriver> cache_ogr;

	static NAN_GETTER(descriptionGetter);

	Driver();
	Driver(GDALDriver *driver);
	Driver(OGRSFDriver *driver);
	inline GDALDriver *getGDALDriver() {
		return this_gdaldriver;
	}
	inline OGRSFDriver *getOGRSFDriver() {
		return this_ogrdriver;
	}

	bool uses_ogr;
private:
	~Driver();
	GDALDriver *this_gdaldriver;
	OGRSFDriver *this_ogrdriver;
};

}
#endif
