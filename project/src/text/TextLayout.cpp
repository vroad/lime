#include <system/System.h>
#include <text/TextLayout.h>
#include <utils/Kinds.h>
#include <utils/PointerUtils.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <hb-ft.h>
#include <hb.h>


namespace lime {
	
	
	TextLayout::TextLayout () {
		
		mFont = 0;
		mHBFont = 0;
		mBuffer = 0;
		mDirection = HB_DIRECTION_INVALID;
		mScript = HB_SCRIPT_INVALID;
		mLanguage = 0;
		
	}
	
	
	bool TextLayout::Init (int direction, const char *script, const char *language) {
		
		if (strlen (script) != 4) return false;
		
		mDirection = (hb_direction_t)direction;
		mLanguage = (void *)hb_language_from_string (language, strlen (language));
		mScript = hb_script_from_string (script, -1);
		
		mBuffer = hb_buffer_create ();
		hb_buffer_set_direction ((hb_buffer_t*)mBuffer, (hb_direction_t)mDirection);
		hb_buffer_set_script ((hb_buffer_t*)mBuffer, (hb_script_t)mScript);
		hb_buffer_set_language ((hb_buffer_t*)mBuffer, (hb_language_t)mLanguage);
		
		return true;
		
	}
	
	
	TextLayout::~TextLayout () {
		
		hb_buffer_destroy ((hb_buffer_t*)mBuffer);
		hb_font_destroy ((hb_font_t*)mHBFont);
		
	}
	
	
	TextLayout* TextLayout::Create (int direction, const char *script, const char *language) {
		
		TextLayout *layout = new TextLayout ();
		
		if (!layout->Init (direction, script, language)) {
			
			delete layout;
			return NULL;
			
		}
		
		return layout;
		
	}
	
	
	value TextLayout::Position (Font *font, size_t size, const char *text, Bytes* bytes) {
		
		if (!font) {
			
			val_throw (alloc_string ("Invalid Font handle"));
			return alloc_null ();
			
		}
		
		if (mFont != font) {
			
			mFont = font;
			hb_font_destroy ((hb_font_t*)mHBFont);
			mHBFont = hb_ft_font_create ((FT_Face)font->face, NULL);
			
		}
		
		font->SetSize (size);
		
		// reset buffer
		hb_buffer_set_direction ((hb_buffer_t*)mBuffer, (hb_direction_t)mDirection);
		hb_buffer_set_script ((hb_buffer_t*)mBuffer, (hb_script_t)mScript);
		hb_buffer_set_language ((hb_buffer_t*)mBuffer, (hb_language_t)mLanguage);
		
		// layout the text
		hb_buffer_add_utf8 ((hb_buffer_t*)mBuffer, text, strlen (text), 0, -1);
		hb_shape ((hb_font_t*)mHBFont, (hb_buffer_t*)mBuffer, NULL, 0);
		
		uint32_t glyph_count;
		hb_glyph_info_t *glyph_info = hb_buffer_get_glyph_infos ((hb_buffer_t*)mBuffer, &glyph_count);
		hb_glyph_position_t *glyph_pos = hb_buffer_get_glyph_positions ((hb_buffer_t*)mBuffer, &glyph_count);
		
		//float hres = 100;
		int posIndex = 0;
		
		int glyphSize = sizeof (GlyphPosition);
		uint32_t dataSize = 4 + (glyph_count * glyphSize);
		
		if (bytes->Length () < dataSize) {
			
			bytes->Resize (dataSize);
			
		}
		
		unsigned char* bytesPosition = bytes->Data ();
		
		*(uint32_t *)(bytesPosition) = glyph_count;
		bytesPosition += 4;
		
		hb_glyph_position_t pos;
		GlyphPosition *data;
		
		for (int i = 0; i < glyph_count; i++) {
			
			pos = glyph_pos[i];
			
			data = (GlyphPosition*)(bytesPosition);
			
			data->index = glyph_info[i].codepoint;
			data->advanceX = (float)(pos.x_advance / (float)(64));
			data->advanceY = (float)(pos.y_advance / (float)64);
			data->offsetX = (float)(pos.x_offset / (float)(64));
			data->offsetY = (float)(pos.y_offset / (float)64);
			
			bytesPosition += glyphSize;
			
		}

		hb_buffer_clear_contents ((hb_buffer_t*)mBuffer);
		return bytes->Value ();
		
	}
	
	
	void TextLayout::SetDirection (int direction) {
		
		mDirection = (hb_direction_t)direction;
		
	}
	
	
	void TextLayout::SetLanguage (const char* language) {
		
		mLanguage = (void *)hb_language_from_string (language, strlen (language));
		
	}
	
	
	void TextLayout::SetScript (const char* script) {
		
		mScript = hb_script_from_string (script, -1);
		
	}
	
	
	value TextLayout_to_val (TextLayout* inInstance) {
		
		return CFFIPointer (inInstance, lime_destroy_abstract<TextLayout>, Kinds::Get ()->TextLayout);
		
	}
	
	
	TextLayout* val_to_TextLayout (value inHandle) {
		
		return lime_abstract_to_pointer<TextLayout> (inHandle, Kinds::Get ()->TextLayout);
		
	}
	
	
}
