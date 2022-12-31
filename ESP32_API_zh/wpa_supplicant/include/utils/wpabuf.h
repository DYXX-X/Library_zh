/*
 * 动态数据缓冲区版权所有（c）2007-2012，Jouni Malinen<j@w1.fi>
 *
 * 该程序是免费软件；您可以根据自由软件基金会发布的GNU通用公共许可证第2版的条款重新分发和/或修改它。
 *
 * 或者，此软件可以根据BSD许可证条款进行分发。
 *
 * 有关详细信息，请参阅自述和复制。
 */

#ifndef WPABUF_H
#define WPABUF_H

/* wpabuf:：buf是指向外部数据的指针*/
#define WPABUF_FLAG_EXT_DATA BIT(0)

/*
 * wpabuf的内部数据结构。请不要从其他地方直接接触。这仅在头文件中定义，以允许来自此文件的内联函数访问数据。
 */
struct wpabuf {
	size_t size; /* 已分配缓冲区的总大小*/
	size_t used; /* 缓冲区中的数据长度*/
	u8 *buf; /* 指向缓冲区头部的指针*/
	unsigned int flags;
	/* 可选地后跟分配的缓冲区*/
};


int wpabuf_resize(struct wpabuf **buf, size_t add_len);
struct wpabuf * wpabuf_alloc(size_t len);
struct wpabuf * wpabuf_alloc_ext_data(u8 *data, size_t len);
struct wpabuf * wpabuf_alloc_copy(const void *data, size_t len);
struct wpabuf * wpabuf_dup(const struct wpabuf *src);
void wpabuf_free(struct wpabuf *buf);
void wpabuf_clear_free(struct wpabuf *buf);
void * wpabuf_put(struct wpabuf *buf, size_t len);
struct wpabuf * wpabuf_concat(struct wpabuf *a, struct wpabuf *b);
struct wpabuf * wpabuf_zeropad(struct wpabuf *buf, size_t len);
void wpabuf_printf(struct wpabuf *buf, const char *fmt, ...) PRINTF_FORMAT(2, 3);


/**
 * wpabuf_size-获取wpabuf缓冲区的当前分配大小
 * @buf: wpabuf缓冲区返回：当前分配的缓冲区大小
 */
static inline size_t wpabuf_size(const struct wpabuf *buf)
{
	return buf->size;
}

/**
 * wpabuf_len-获取wpabuf缓冲区数据的当前长度
 * @buf: wpabuf buffer返回：当前使用的缓冲区长度
 */
static inline size_t wpabuf_len(const struct wpabuf *buf)
{
	return buf->used;
}

/**
 * wpabuf_tailroom-获取缓冲区末尾的可用尾部空间大小
 * @buf: wpabufbuffer返回：缓冲区末尾可用空间的尾部空间（以字节为单位）
 */
static inline size_t wpabuf_tailroom(const struct wpabuf *buf)
{
	return buf->size - buf->used;
}

/**
 * wpabuf_head-获取指向缓冲区数据头部的指针
 * @buf: wpabuf缓冲区返回：指向缓冲区数据头的指针
 */
static inline const void * wpabuf_head(const struct wpabuf *buf)
{
	return buf->buf;
}

static inline const u8 * wpabuf_head_u8(const struct wpabuf *buf)
{
	return wpabuf_head(buf);
}

/**
 * wpabuf_mhead-获取指向缓冲区数据头部的可修改指针
 * @buf: wpabuf缓冲区返回：指向缓冲区数据头的指针
 */
static inline void * wpabuf_mhead(struct wpabuf *buf)
{
	return buf->buf;
}

static inline u8 * wpabuf_mhead_u8(struct wpabuf *buf)
{
	return wpabuf_mhead(buf);
}

static inline void wpabuf_put_u8(struct wpabuf *buf, u8 data)
{
	u8 *pos = wpabuf_put(buf, 1);
	*pos = data;
}

static inline void wpabuf_put_le16(struct wpabuf *buf, u16 data)
{
	u8 *pos = wpabuf_put(buf, 2);
	WPA_PUT_LE16(pos, data);
}

static inline void wpabuf_put_le32(struct wpabuf *buf, u32 data)
{
	u8 *pos = wpabuf_put(buf, 4);
	WPA_PUT_LE32(pos, data);
}

static inline void wpabuf_put_be16(struct wpabuf *buf, u16 data)
{
	u8 *pos = wpabuf_put(buf, 2);
	WPA_PUT_BE16(pos, data);
}

static inline void wpabuf_put_be24(struct wpabuf *buf, u32 data)
{
	u8 *pos = wpabuf_put(buf, 3);
	WPA_PUT_BE24(pos, data);
}

static inline void wpabuf_put_be32(struct wpabuf *buf, u32 data)
{
	u8 *pos = wpabuf_put(buf, 4);
	WPA_PUT_BE32(pos, data);
}

static inline void wpabuf_put_data(struct wpabuf *buf, const void *data,
				   size_t len)
{
	if (data)
		os_memcpy(wpabuf_put(buf, len), data, len);
}

static inline void wpabuf_put_buf(struct wpabuf *dst,
				  const struct wpabuf *src)
{
	wpabuf_put_data(dst, wpabuf_head(src), wpabuf_len(src));
}

static inline void wpabuf_set(struct wpabuf *buf, const void *data, size_t len)
{
	buf->buf = (u8 *) data;
	buf->flags = WPABUF_FLAG_EXT_DATA;
	buf->size = buf->used = len;
}

static inline void wpabuf_put_str(struct wpabuf *dst, const char *str)
{
	wpabuf_put_data(dst, str, os_strlen(str));
}

#endif /* WPABUF_H */

