from django import forms

class CommentForm(forms.Form):
    name = forms.CharField(label='称呼', max_length = 16, error_messages = {
        'required' : '请填写您的称呼',
        'max_length' : '称呼太长',
    })
    
    email = forms.EmailField(label = '标签', error_messages = {
        'required' : '请填写您的邮箱',
        'invalid' : '邮箱格式不正确',
    })

    content = forms.CharField(label = '评论内容', max_length = 140, error_messages = {
        'required' : '请填写您的评论内容',
        'max_length' : '评论内容太长',
    })


