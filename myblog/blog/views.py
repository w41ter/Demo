from django.shortcuts import render
from django.http import Http404
from .forms import CommentForm
from .models import Blog, Comment

def get_blogs(request):
    content = {
        'blogs' : Blog.objects.all().order_by('-created')
    }
    return render(request, 'blog-list.html', content)

def get_detail(request, blog_id):
    try:
        blog = Blog.objects.get(id = blog_id)
    except Blog.DoesNotExist:
        raise Http404

    if request.method == 'GET':
        form = CommentForm()
    else:
        form = CommentForm(request.POST)
        if form.is_valid():
            cleaned_data = form.cleaned_data
            cleaned_data['blog'] = blog
            Comment.objects.create(**cleaned_data)

    content = {
        'blog' : blog,
        'comments' : blog.comment_set.all().order_by('-created'),
        'form' : form,
    }

    return render(request, 'blog-detail.html', content)

