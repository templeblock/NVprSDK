
/*
 * Copyright 2010 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef SkPDFStream_DEFINED
#define SkPDFStream_DEFINED

#include "SkPDFTypes.h"
#include "SkRefCnt.h"
#include "SkStream.h"
#include "SkTemplates.h"

class SkPDFCatalog;

/** \class SkPDFStream

    A stream object in a PDF.  Note, all streams must be indirect objects (via
    SkObjRef).
*/
class SkPDFStream : public SkPDFDict {
public:
    /** Create a PDF stream. A Length entry is automatically added to the
     *  stream dictionary. The stream may be retained (stream->ref() may be
     *  called) so its contents must not be changed after calling this.
     *  @param data  The data part of the stream.
     */
    explicit SkPDFStream(SkData* data);
    /** Deprecated constructor. */
    explicit SkPDFStream(SkStream* stream);
    /** Create a PDF stream with the same content and dictionary entries
     *  as the passed one.
     */
    explicit SkPDFStream(const SkPDFStream& pdfStream);
    virtual ~SkPDFStream();

    // The SkPDFObject interface.
    virtual void emitObject(SkWStream* stream, SkPDFCatalog* catalog,
                            bool indirect);
    virtual size_t getOutputSize(SkPDFCatalog* catalog, bool indirect);

protected:
    /* Create a PDF stream with no data.  The setData method must be called to
     * set the data.
     */
    SkPDFStream();

    void setData(SkStream* stream);

private:
    enum State {
        kUnused_State,         //!< The stream hasn't been requested yet.
        kNoCompression_State,  //!< The stream's been requested in an
                               //   uncompressed form.
        kCompressed_State,     //!< The stream's already been compressed.
    };
    // Indicates what form (or if) the stream has been requested.
    State fState;

    // TODO(vandebo): Use SkData (after removing deprecated constructor).
    SkRefPtr<SkStream> fData;
    SkRefPtr<SkPDFStream> fSubstitute;

    typedef SkPDFDict INHERITED;

    // Populate the stream dictionary.  This method returns false if
    // fSubstitute should be used.
    bool populate(SkPDFCatalog* catalog);
};

#endif
