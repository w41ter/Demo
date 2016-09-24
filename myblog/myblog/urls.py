from django.conf.urls import patterns, url
from blog import views
from django.contrib import admin

urlpatterns = patterns(
    url(r'^admin/$', admin.site.urls),
    url(r'^$', views.get_blogs, name = 'blog_get_blogs'),
    url(r'^detail/(?P<blog_id>\d+)/$', views.get_detail, name = 'blog_get_detail'),
)
