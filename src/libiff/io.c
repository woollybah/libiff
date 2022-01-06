/*
 * Copyright (c) 2012 Sander van der Burg
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "io.h"
#include "error.h"

int IFF_readUByte(io_context * context, IFF_UByte *value, const IFF_ID chunkId, const char *attributeName)
{
    if((context->io.eof)(context->userData))
    {
    IFF_readError(chunkId, attributeName);
	return FALSE;
    }
    char byte;

    if((context->io.read)(context->userData,&byte,1) == 0)
    {
    IFF_readError(chunkId, attributeName);
	return FALSE;
    }
    else
    {
	*value = byte;
	return TRUE;
    }
}

int IFF_writeUByte(FILE *file, const IFF_UByte value, const IFF_ID chunkId, const char *attributeName)
{
    if(fputc(value, file) == EOF)
    {
	IFF_writeError(chunkId, attributeName);
	return FALSE;
    }
    else
	return TRUE;
}

int IFF_readUWord(io_context * context, IFF_UWord *value, const IFF_ID chunkId, const char *attributeName)
{
    IFF_UWord readUWord;
    
    if((context->io.read)(context->userData,&readUWord,sizeof(IFF_UWord)) > 0)
    {
#if IFF_BIG_ENDIAN == 1
	*value = readUWord;
#else
	/* Byte swap it */
	*value = (readUWord & 0xff) << 8 | (readUWord & 0xff00) >> 8;
#endif
	
	return TRUE;
    }
    else
    {
	IFF_readError(chunkId, attributeName);
	return FALSE;
    }
}

int IFF_writeUWord(FILE *file, const IFF_UWord value, const IFF_ID chunkId, const char *attributeName)
{
#if IFF_BIG_ENDIAN == 1
    IFF_UWord writeUWord = value;
#else
    /* Byte swap it */
    IFF_UWord writeUWord = (value & 0xff) << 8 | (value & 0xff00) >> 8;
#endif

    if(fwrite(&writeUWord, sizeof(IFF_UWord), 1, file) == 1)
	return TRUE;
    else
    {
	IFF_writeError(chunkId, attributeName);
	return FALSE;
    }
}

int IFF_readWord(io_context * context, IFF_Word *value, const IFF_ID chunkId, const char *attributeName)
{
    IFF_Word readWord;
    
    if((context->io.read)(context->userData,&readWord,sizeof(IFF_Word)) > 0)
    {
#if IFF_BIG_ENDIAN == 1
	*value = readWord;
#else
	/* Byte swap it */
	*value = (readWord & 0xff) << 8 | (readWord & 0xff00) >> 8;
#endif
	return TRUE;
    }
    else
    {
	IFF_readError(chunkId, attributeName);
	return FALSE;
    }
}

int IFF_writeWord(FILE *file, const IFF_Word value, const IFF_ID chunkId, const char *attributeName)
{
#if IFF_BIG_ENDIAN == 1
    IFF_Word writeWord = value;
#else
    IFF_Word writeWord = (value & 0xff) << 8 | (value & 0xff00) >> 8;
#endif

    if(fwrite(&writeWord, sizeof(IFF_Word), 1, file) == 1)
	return TRUE;
    else
    {
	IFF_writeError(chunkId, attributeName);
	return FALSE;
    }
}

int IFF_readULong(io_context * context, IFF_ULong *value, const IFF_ID chunkId, const char *attributeName)
{
    IFF_ULong readValue;
    
    if((context->io.read)(context->userData,&readValue,sizeof(IFF_ULong)) > 0)
    {
#if IFF_BIG_ENDIAN == 1
	*value = readValue;
#else
	/* Byte swap it */
	*value = (readValue & 0xff) << 24 | (readValue & 0xff00) << 8 | (readValue & 0xff0000) >> 8 | (readValue & 0xff000000) >> 24;
#endif
	return TRUE;
    }
    else
    {
	IFF_readError(chunkId, attributeName);
	return FALSE;
    }
}

int IFF_writeULong(FILE *file, const IFF_ULong value, const IFF_ID chunkId, const char *attributeName)
{
#if IFF_BIG_ENDIAN == 1
    IFF_ULong writeValue = value;
#else
    /* Byte swap it */
    IFF_ULong writeValue = (value & 0xff) << 24 | (value & 0xff00) << 8 | (value & 0xff0000) >> 8 | (value & 0xff000000) >> 24;
#endif

    if(fwrite(&writeValue, sizeof(IFF_ULong), 1, file) == 1)
	return TRUE;
    else
    {
	IFF_writeError(chunkId, attributeName);
	return FALSE;
    }
}

int IFF_readLong(io_context * context, IFF_Long *value, const IFF_ID chunkId, const char *attributeName)
{
    IFF_Long readValue;
    
    if((context->io.read)(context->userData,&readValue,sizeof(IFF_Long)) > 0)
    {
#if IFF_BIG_ENDIAN == 1
	*value = readValue;
#else
	/* Byte swap it */
	*value = (readValue & 0xff) << 24 | (readValue & 0xff00) << 8 | (readValue & 0xff0000) >> 8 | (readValue & 0xff000000) >> 24;
#endif
	return TRUE;
    }
    else
    {
	IFF_readError(chunkId, attributeName);
	return FALSE;
    }
}

int IFF_writeLong(FILE *file, const IFF_Long value, const IFF_ID chunkId, const char *attributeName)
{
#if IFF_BIG_ENDIAN == 1
    IFF_Long writeValue = value;
#else
    /* Byte swap it */
    IFF_Long writeValue = (value & 0xff) << 24 | (value & 0xff00) << 8 | (value & 0xff0000) >> 8 | (value & 0xff000000) >> 24;
#endif

    if(fwrite(&writeValue, sizeof(IFF_Long), 1, file) == 1)
	return TRUE;
    else
    {
	IFF_writeError(chunkId, attributeName);
	return FALSE;
    }
}

int IFF_readPaddingByte(io_context * context, const IFF_Long chunkSize, const IFF_ID chunkId)
{
    if(chunkSize % 2 != 0) /* Check whether the chunk size is an odd number */
    {
        int err = (context->io.eof)(context->userData);
        char byte;

        if(!err)
        {
            err = (context->io.read)(context->userData,&byte,1) == 0; /* Read padding byte */
        }
	
        if(err) /* We shouldn't have reached the EOF yet */
        {
    	    IFF_error("Unexpected end of file, while reading padding byte of '");
    	    IFF_errorId(chunkId);
    	    IFF_error("'\n");
	    return FALSE;
	}
	else if(byte != 0) /* Normally, a padding byte is 0, warn if this is not the case */
	    IFF_error("WARNING: Padding byte is non-zero!\n");
    }
    
    return TRUE;
}

int IFF_writePaddingByte(FILE *file, const IFF_Long chunkSize, const IFF_ID chunkId)
{
    if(chunkSize % 2 != 0) /* Check whether the chunk size is an odd number */
    {
	if(fputc('\0', file) == EOF)
	{
	    IFF_error("Cannot write padding byte of '");
	    IFF_errorId(chunkId);
	    IFF_error("'\n");
	    return FALSE;
	}
	else
	    return TRUE;
    }
    
    return TRUE;
}
