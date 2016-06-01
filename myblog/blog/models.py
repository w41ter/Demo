from django.db import models

class Category(models.Model):
    name = models.CharField('名称', max_length = 16)

    def __str__(self):
        return self.name

class Tag(models.Model):
    name = models.CharField('名称', max_length = 16)

    def __str__(self):
        return self.name

class Blog(models.Model):
    title = models.CharField('标题', max_length = 32)
    author = models.CharField('作者', max_length = 16)
    content = models.TextField('正文')
    created = models.DateTimeField('发布时间', auto_now_add = True)
    
    category = models.ForeignKey(Category, verbose_name = 'category')
    tags = models.ManyToManyField(Tag, verbose_name = 'tags')

    def __str__(self):
        return self.title

class Comment(models.Model):
    blog = models.ForeignKey(Blog, verbose_name = 'blog')

    name = models.CharField('name', max_length = 16)
    email = models.EmailField('email')
    content = models.CharField('content', max_length = 140)

    created = models.DateTimeField('发布时间', auto_now_add = True)

    def __str__(self):
        return "%s's comment." % self.name

