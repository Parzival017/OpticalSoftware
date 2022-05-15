import time
import requests
import random
import string
openid="{}_{}".format("".join([random.choice(string.ascii_lowercase) for i in range(20)]),random.randint(1000000,9999999))
print(openid)
tenantCode="4142010487" #华科的
print("请确认已经在'我的'里面解绑微信,请尽量让软件运行完毕,如中断运行无法登录,请前往https://weiban.mycourse.cn/index.html#/login解绑微信")
stuNum=input("请输入学号：")
data={
    "tenantCode": tenantCode,
    "sno": stuNum,
    "password": stuNum,
    "openid": openid,
}
res=requests.post("https://weiban.mycourse.cn/pharos/login/getUserInfo.do",data=data)
print(res.text)
yes=input("该信息是否正确？(y/n)")
if yes!="y":
    exit()

data={
    "tenantCode": tenantCode,
    "sno": stuNum,
    "password": stuNum,
    "openid": openid,
    "type": "1"
}
res=requests.post("https://weiban.mycourse.cn/pharos/login/bindWechat.do",data=data)
print(res.text)
token=res.json()["data"]["token"]
userId=res.json()["data"]["userId"]
userName=res.json()["data"]["userName"]

data={
    "tenantCode": tenantCode,
    "userId": userId,
    "token": token,
    "limit": "10",
}
res=requests.post("https://weiban.mycourse.cn/pharos/index/listStudyTask.do",data=data)
print(res.text)
userProjectId=""
for i in res.json()["data"]:
    if(i["projectName"]=="本科生安全教育"):
        userProjectId=i["userProjectId"]

data={
    "tenantCode": tenantCode,
    "userId": userId,
    "token": token,
    "userProjectId": userProjectId,
    "chooseType":3
}
res=requests.post("https://weiban.mycourse.cn/pharos/usercourse/listCategory.do",data=data)
print(res.text)

for i in res.json()["data"]:
    categoryCode=i["categoryCode"]
    data={
        "tenantCode": tenantCode,
        "userId": userId,
        "token": token,
        "userProjectId": userProjectId,
        "categoryCode": categoryCode,
        "chooseType":3
    }
    nres=requests.post("https://weiban.mycourse.cn/pharos/usercourse/listCourse.do",data=data)
    print(nres.text)

    for j in nres.json()["data"]:
        if(j["finished"]==1):
            print("检测到完成的一节课，已跳过")
            continue
        userCourseId=j["userCourseId"]
        data={
            "tenantCode": tenantCode,
            "userId": userId,
            "token": token,
            "userProjectId": userProjectId,
            "courseId": j["resourceId"],
        }
        nnres=requests.post("https://weiban.mycourse.cn/pharos/usercourse/study.do",data=data)
        print(nnres.text)

        nnres=requests.post("https://weiban.mycourse.cn/pharos/usercourse/getCourseUrl.do",data=data)
        print(nnres.text)

        print("延迟十秒，否则不生效")
        time.sleep(10)

        data={
            "userCourseId": userCourseId,
            "tenantCode": tenantCode,
        }
        nnres=requests.post("https://weiban.mycourse.cn/pharos/usercourse/finish.do",data=data)
        print(nnres.text)
data={
    "tenantCode": tenantCode,
    "userId": userId,
    "token": token,
}
res=requests.post("https://weiban.mycourse.cn/pharos/my/cancelBindWechat.do",data=data)
print(res.text)
print("完成")