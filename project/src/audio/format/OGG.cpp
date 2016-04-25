#include <audio/format/OGG.h>
#include <audio/OggAudioStream.h>
#include <system/System.h>
#include <vorbis/vorbisfile.h>

// 0 for Little-Endian, 1 for Big-Endian
#ifdef HXCPP_BIG_ENDIAN
#define BUFFER_READ_TYPE 1
#else
#define BUFFER_READ_TYPE 0
#endif

#define READ_MAX 4096

namespace lime {
	
	
	static size_t OAL_OggBufferRead (void* dest, size_t eltSize, size_t nelts, OAL_OggMemoryFile* src) {
		
		size_t len = eltSize * nelts;
		
		if ((src->pos + len) > src->size) {
			
			len = src->size - src->pos;
			
		}
		
		if (len > 0) {
			
			memcpy (dest, (src->data + src->pos), len);
			src->pos += len;
			
		}
		
		return len;
		
	}
	
	
	static int OAL_OggBufferSeek (OAL_OggMemoryFile* src, ogg_int64_t pos, int whence) {
		
		switch (whence) {
			
			case SEEK_CUR:
				
				src->pos += pos;
				break;
			
			case SEEK_END:
				
				src->pos = src->size - pos;
				break;
			
			case SEEK_SET:
				
				src->pos = pos;
				break;
			
			default:
				
				return -1;
			
		}
		
		if (src->pos < 0) {
			
			src->pos = 0;
			return -1;
			
		}
		
		if (src->pos > src->size) {
			
			return -1;
			
		}
		
		return 0;
		
	}
	
	
	static int OAL_OggBufferClose (OAL_OggMemoryFile* src) {
		
		return 0;
		
	}
	
	
	static long OAL_OggBufferTell (OAL_OggMemoryFile *src) {
		
		return src->pos;
		
	}
	
	
	static ov_callbacks OAL_CALLBACKS_BUFFER = {
		
		(size_t (*)(void *, size_t, size_t, void *)) OAL_OggBufferRead,
		(int (*)(void *, ogg_int64_t, int)) OAL_OggBufferSeek,
		(int (*)(void *)) OAL_OggBufferClose,
		(long (*)(void *)) OAL_OggBufferTell
		
	};
	
	
	bool OGG::Decode (Resource *resource, AudioBuffer *audioBuffer, bool stream) {
		
		OggVorbis_File *oggFile = new OggVorbis_File ();
		OAL_OggMemoryFile *fakeFile = NULL;
		
		if (resource->path) {
			
			FILE_HANDLE *file = lime::fopen (resource->path, "rb");
			
			if (!file) {
				
				ov_clear (oggFile);
				return false;
				
			}
			
			if (file->isFile ()) {
				
				if (ov_open (file->getFile (), oggFile, NULL, file->getLength ()) != 0) {
					
					ov_clear (oggFile);
					lime::fclose (file);
					return false;
					
				}
				
			} else {
				
				audioBuffer->sourceData = new Bytes ();
				int status = audioBuffer->sourceData->ReadFile (file);
				lime::fclose (file);
				file = 0;
				
				if (!status) {
					
					ov_clear (oggFile);
					delete audioBuffer->sourceData;
					return false;
					
				}
				
				fakeFile = new OAL_OggMemoryFile ();
				fakeFile->data = audioBuffer->sourceData->Data ();
				fakeFile->size = audioBuffer->sourceData->Length ();
				fakeFile->pos = 0;
				
				if (ov_open_callbacks (fakeFile, oggFile, NULL, 0, OAL_CALLBACKS_BUFFER) != 0) {
					
					ov_clear (oggFile);
					delete audioBuffer->sourceData;
					delete fakeFile;
					return false;
					
				}
				
			}
			
		} else {
			
			audioBuffer->sourceData = new Bytes (*resource->data);
			fakeFile = new OAL_OggMemoryFile ();
			fakeFile->data = audioBuffer->sourceData->Data ();
			fakeFile->size = audioBuffer->sourceData->Length ();
			fakeFile->pos = 0;
			
			if (ov_open_callbacks (fakeFile, oggFile, NULL, 0, OAL_CALLBACKS_BUFFER) != 0) {
				
				ov_clear (oggFile);
				delete audioBuffer->sourceData;
				delete fakeFile;
				return false;
				
			}
			
		}
		
		int bitStream;
		long bytes = 1;
		int totalBytes = 0;
		
		vorbis_info *pInfo = ov_info (oggFile, -1);
		
		if (pInfo == NULL) {
			
			//LOG_SOUND("FAILED TO READ OGG SOUND INFO, IS THIS EVEN AN OGG FILE?\n");
			ov_clear (oggFile);
			delete audioBuffer->sourceData;
			delete fakeFile;
			return false;
			
		}
		
		audioBuffer->channels = pInfo->channels;
		audioBuffer->sampleRate = pInfo->rate;
		
		audioBuffer->bitsPerSample = 16;
		
		int dataLength = ov_pcm_total (oggFile, -1) * audioBuffer->channels * audioBuffer->bitsPerSample / 8;
		audioBuffer->length = dataLength;
		
		if (!stream) {
			
			audioBuffer->data = new Bytes (dataLength);
			
			while (bytes > 0) {
				
				bytes = ov_read (oggFile, (char *)audioBuffer->data->Data () + totalBytes, READ_MAX, BUFFER_READ_TYPE, 2, 1, &bitStream);
				totalBytes += bytes;
				
			}
			
			if (dataLength != totalBytes) {
				
				audioBuffer->data->Resize (totalBytes);
				
			}
			
		}
		
		if (!stream) {
			
			ov_clear (oggFile);
			oggFile = NULL;
			delete audioBuffer->sourceData;
			delete fakeFile;
			audioBuffer->sourceData = NULL;
			
		} else {
			
			audioBuffer->handle = new OggAudioStream (oggFile, fakeFile);
			
		}
		
		return true;
		
	}
	
	bool OGG::SeekStream (OggVorbis_File *oggFile, double seconds) {
		
		return ov_time_seek (oggFile, seconds) == 0;
		
	}
	
	int OGG::DecodeStream (OggVorbis_File *oggFile, Bytes *data, int readSize, int writeOffset) {
		
		int bitStream;
		int remainBytes = readSize;
		int totalBytes = 0;
		
		int bytes;
		do {
			
			size_t readBufferSize = READ_MAX < remainBytes ? READ_MAX : remainBytes;
			bytes = ov_read (oggFile, ((char *)data->Data ()) + writeOffset + totalBytes, readBufferSize, BUFFER_READ_TYPE, 2, 1, &bitStream);
			remainBytes -= bytes;
			totalBytes += bytes;
			
		} while (bytes > 0 && remainBytes > 0);

		return totalBytes;
	}
	
}