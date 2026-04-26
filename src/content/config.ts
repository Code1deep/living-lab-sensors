import { defineCollection, z } from 'astro:content';

const blogCollection = defineCollection({
  schema: z.object({
    title: z.string(),
    description: z.string(),
    keywords: z.string().optional(),
    ogImage: z.string().optional(),
    pubDate: z.string(),
    author: z.string().default("A. Elbah"),
  }),
});

export const collections = {
  'blog': blogCollection,
};
