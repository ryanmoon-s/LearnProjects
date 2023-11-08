# snippets

# 小组开发机

小组开发机 
9.135.38.11

9.134.71.236
yingyongkaifazu_dylan_2023

# 审计上报
``` c++
    wwinneropen::AuditData onedata;
    onedata.vid = req.vid();
    m_reporter.Report({onedata});

	wwinneropen::AuditData onedata;
    onedata.corpid = req.corpid();
    m_reporter.Report({onedata});
	
	m_reporter.Report(vector<wwinneropen::AuditData>());
	
	vector<wwinneropen::AuditData> vecAuditData;
	wwinneropen::AuditData onedata;
    onedata.corpid = req.corpid();
	vecAuditData.push_back(onedata);
	m_reporter.Report(vecAuditData);
```

# 参数校验
``` protobuf
[
        ( validate.field_is_vid ) = true
    ]
	
[
        ( validate.field_is_corpid ) = true
    ]
	
[
        ( validate.field_is_vid ) = true,
		( validate.field_must_check_rule ) = false
    ]
	
[
        ( validate.field_is_corpid ) = true,
		( validate.field_must_check_rule ) = false
    ]
	
// string
[
        ( validate.field_length_min ) = 1,
		( validate.field_must_check_rule ) = false
    ]

// int等
[
        ( validate.field_range_min ) = "1",
		( validate.field_must_check_rule ) = false
    ]

// repeated个数
[
        ( validate.field_item_min ) = 1,
		( validate.field_item_max ) = 20
    ]

// int等类型范围
[
        ( validate.field_range_min ) = "0",
        ( validate.field_range_max ) = "1"
    ]

// 子字段必须存在	
	( validate.subfield_must_exist ) = "1,2"

/ 不一定校验
( validate.field_must_exist ) = true

// cgi鉴权替换
(serviceauth.field_need_replace) = true

(serviceauth.subfield_need_replace) = ""

import "comm2/validatelib/validate_extend.proto";
"//comm2/validatelib:validaterequest",

```

# 本地版

【本地版】
local_group2_dev3.0
wwlocalinnerbroker
--story=876710875 客户联系
https://tapd.woa.com/rtxpm/prong/stories/view/1010121621881124703

1、wwaccountinnerbroker->wwlocalinnerbroker：
UpdateUser
CreateVidForUserBatch
AddUser
DelUser

# 一些脚本

``` bash
wwcorpinnerbroker拉取回包过大
awk '{a=$8;b=$10;num=substr(b,0,length(b)-1);corpid=substr(a,0,length(a)-1);arr[corpid]+=num}END{for(key in arr)print key,arr[key]}' | sort -nk2
wwcorphttpbroker拉取回包过大
awk '{a=$14;b=$12;num=substr(b,0,length(b)-1);corpid=substr(a,0,length(a)-1);arr[corpid]+=num}END{for(key in arr)print key,arr[key]}' | sort -nk2

翻译出来的语句转换成文案系统CamelCase风格
sed -E 's/ ([a-z])/\U\1/g;s/[.,?_-]+//g' | awk '{print "K"$0}'

core.log分析：
cat xx | egrep '\[0x[0-9a-z]+' -o | sed 's/\[//' | awk '{r=r$1" "}END{print r}'
echo '' | xargs addr2line -e sbin/wwschoolroomsvr -a

过滤数据包：
过滤长度
awk '{len=length($0);if(len != 17)print NR, $0}'
看看不合规矩是什么数据：
sed '463284p' -n src_600w.txt
删除有问题的行：删除一次要重新过滤，找行数
sed '4566495d' -i src_600w.txt

搜索RUN日志看网络收发包大小
<2> <wwcorphttpbroker-BatchGetMyParty(64423,64423,50024)> 2023-05-25 09:12:00 1684977119196573610438964 RUN 0 29 UIN 1688857327379313 0 CLI 11.181.116.60 11.181.116.60 io 487 275
awk  -F'[-( ]' '{xin=$20;xout=$21;xfunc=$3;arrin[xfunc]+=xin;arrout[xfunc]+=xout}END{for(keyin in arrin)print keyin,arrin[keyin]}' | sort -nrk2
awk  -F'[-( ]' '{xin=$20;xout=$21;xfunc=$3;arrin[xfunc]+=xin;arrout[xfunc]+=xout}END{for(keyout in arrout)print keyout,arrout[keyout]}' | sort -nrk2

事务xmq重试到达上线
wwtransactionxmq
rty_alrt
wwschoollogicsvr

wwtoolsvr2磁盘空间：
quota -usv arashi
```

# 测试数据

// 成都十中
schoolid: 15199649577378187
partyid: 15481127740619777
班级群roomid: 10965368976721375
学生群roomid：10859904052509966
升年级tableid: 774

相册测试partyid：15481124519590329
roomid: 10920970489880189

我的vid: 1688857060423065
兔兔vid: 1688858038431327
无关vid: 1688857772472647
我的xid: 7881302431065444

作业homework_id: 7251770063202284399
打卡checkin_taskid: 7254922625114233594
通知notify_taskid: 7254931651648176415
局校通知msgid: 7255135938556285637
收款projectid：7257087059986932669

// 家校2.0
1970324974073175
1688855763478598

# broker接口下线


微盘、企业邮迁移，旧接口梳理下线（不紧急，有时间就做）
#include "wework/wwcomm/wwerrcodedef.h"

return WWCmdOffline; // 接口下线


# AI辅助审核

ssh spananti@9.91.67.170
NLP@span123
antispam@NLP123
conda activate ww_chatglm_svr
conda activate llm_spanti_svr

# 岗位识别

最优模型放在、训练、验证代码及数据集/dockerdata/buyllm/yalehe/hutong/train
ssh buyllm@9.91.1.179
NLP@buy1234

loganyu@wwdatamindtoolsvr2[qq]:/data1/loganyu> ./position_feature_enabled  -f GetPositionAllUserFeature -p corpid_path
按照企业捞取用户特征，分隔符是| , 输入企业id，一行一个

// 跑特征
./position_feature_enabled -f GetPositionAllUserFeature -p corpids -n 20 -c 10 -o feature_new_sort

// 特征里面的企业数
cat feature_new_sort | awk -F'|' '{print $56}' | sed 1d | sort -u | wc -l

// 提取特征里面的corpid vid
sed 1d feature_all_corpid_clean | awk -F'|' '{if($56>0&&$1>0)print $56,$1}' | sort -u > feature_all_corpid_l_corpid_vid

account_position == 0
mainparty_sub_depth == 0 && mainparty_member_count == 1

20G->120G

# 家校脚本
``` bash
部门：1学校 2学区 3学段 4年级 5班级 6学生
用户：1校长 2班主任 3任课老师 4 家长 5年级长 6学区负责人 7学段负责人
	老师staffid（vid）挂在1、2、3、4、5下面
	家长staffid挂在6下面

### corpid -> schoolid
./innercall -f hikit -m wwadminsvr -n GetAdminMini -j '{"corpid":1970324993514818}' | grep schoolid

### partyid 查学生
./innercall -f hikit -m wwschoolarchsvr -n GetParty -j '{"schoolid":15199652427611186,"partyid":15481126441603137}'

### partyid 班级partyid，查下面的所有：老师vid
./innercall -f hikit -m wwschoolarchsvr -n GetPartyMember -j '{"schoolid":15199652427611186,"partyid":15481126441603137}'
### partyid 班级partyid，查下面的指定：老师vid
./innercall -f hikit -m wwschoolarchsvr -n GetMember -j '{"schoolid":15199652427611186,"partyid":15481126441603137,"staffid":1688855631495544}'

### 家长staffid 查staffinfo
./ww_school_tool_t -f GetStaffInfo -a 15762599165350878 -s 15199650139376026
### 家长staffid 查学生party
./innercall -f hikit -m wwschoolarchsvr -n GetMyParty -j '{"schoolid":15199650139376026,"staffid":15762599165350878}'

### partyid 用班级partyid查家长 数量
./innercall -f hikit -m wwschoolarchsvr -n BatchGetSubPartyAndPartyUser -j '{"partyids":[15481126441603137]}' -u 15199652427611186 | grep "type: 4" | wc -l

### partyid 用班级partyid查学生 数量
./innercall -f hikit -m wwschoolarchsvr -n BatchGetSubPartyAndPartyUser -j '{"partyids":[15481126441603137]}' -u 15199652427611186 | grep "level: 6" | wc -l

### 获取所有同类 部门
1学校 2学区 3学段 4年级 5班级 6学生
./innercall -f hikit -m wwschoolarchsvr -n GetAllPartyByType -j '{"schoolid":15199648965378325,"type_list":[6]}' 

### 获取所有同类 成员
1校长 2班主任 3任课老师 4 家长 5年级长 6学区负责人 7学段负责人
./innercall -f hikit -m wwschoolarchsvr -n GetAllMembersByType -j '{"schoolid":15199652427611186,"type_list":[4]}'
```

# CommStrkvClear

``` bash
### 课程群，使用扩散
./innercall -f hikit -m wwcommstrkvsvr -n Set -j '{"type":80,"key":"CreateCourseRoomFolder_1688857581484203","value":""}'

# 岗位识别结果
### 查
./innercall -f hikit -m wwdataminingsvr -n GetUserRankAndPosition -j '{"corpid":1970325963002152,"vid":1688858166474894,"cache_valid_time":10}' -t 1052 -a wwschoolsvr
### 高校-学生
./innercall -f hikit -m wwdataminingsvr -n StoreUserPredictResult -j '{"corpid": 1970325893009821, "predict_result": [{"vid": 1688857581484203, "rank_type": 0, "position_type": 43, "predict_time": 1699342956}]}'
### 高校-上课的老师
./innercall -f hikit -m wwdataminingsvr -n StoreUserPredictResult -j '{"corpid": 1970325963002152, "predict_result": [{"vid": 1688858166474894, "rank_type": 0, "position_type": 34001, "predict_time": 1699342956}]}' -t 1052 -a wwschoolsvr
```

# 课程表脚本

``` bash
### 拉取一个vid的所有日历
./innercall -f hikit -m wwcalendarsvr -n BatchGetUsrCalendar -j '{"vid":1688855790385249}'
### 批量拉取日历的基础信息
./innercall -f hikit -m wwcalendarlogicsvr -n BatchGetCalendarDetail -j '{"cal_id":["18008604958100232"]}'
### 拉取日历下的所有日程
./innercall -f hikit -m wwcalendarsvr -n GetScheduleIndexList -j '{"vid":18008604958100232,"beg_id":0,"seq":0,"limit":5000,"time":0,"update_time":0,"with_qy":false,"start_time":0,"end_time":0,"get_start_time":0,"b_desc":false}'
### 导入信息：导入状态、版本、是否是学生、原始网页html数据（曾经有bug，人维度覆盖，要遍历全企业找一下）
/innercall -f hikit -m wwschoolschedulesvr -n GetScheduleUserImportInfo -j '{"vid":1688855790385249,"corpid":1970324941005315,"b_need_page_data":false}' -t 1052 -a wwschoolsvr
### 用户维度的日历信息：开学时间、上课时间、一节课时长、schedule_str原始json、cal_id
./innercall -f hikit -m wwschoolschedulesvr -n GetUserDetailedScheduleInfo -j '{"vid":1688855790385249,"corpid":1970324941005315,"cal_id":["18008604958100232"]}' -t 1052 -a wwschoolsvr
```

# timer修复

升年级：4544971 appinfo: busi_schoolid
1011
周一 1%		11		【done】
周二 10%	100		【done】
周三 100%	900

局校看板：228720 appinfo: busi_school_board_【done】
周二 1% 	10		【done】
周三 10%	100		【done】
周四 100%	1000	【done】

加入班级群：533 appinfo: busi_repeated_notify_join_classroom【done】
剩下：
busi_logoff_timer 2	【done】
busi_pre_logoff_timer_ 2 【done】

# 版本需求
文案：
270158
270224
270225
270253
270294
270295
270296
要上配置：
wwschoollogic
wwschoolxmq（uin串行化）
wwcorpmetalogic（提单编上去后，jarry上线）

# 岗位识别临时

岗位识别为leader里面拉100条出来review
23w vid，跑一个结果，原来有多少关系对，过滤后还剩下多少关系对
描述改一下


特征统计值：
all: 10559619
user config: 392812

覆盖率
level:1, job cover:  1543524 251611 180328
level:1, user cover:  392812 114209 0
level:1, all cover:  311719 2215789
dump end, level:1

岗位识别为leader：共154w，规则覆盖25w，模型覆盖

ag-20231103_031349

```
[[29890     7]
 [   12 30091]]
              precision    recall  f1-score   support

           0       1.00      1.00      1.00     29897
           1       1.00      1.00      1.00     30103

    accuracy                           1.00     60000
   macro avg       1.00      1.00      1.00     60000
weighted avg       1.00      1.00      1.00     60000
```

23w接收过周报的人里面有说话的：102046
规则认为是leader：17300，占比17%
模型预测为leader：75535，占比74%
去重统计：84309，占比82.6%

10月过往接收过周报的一级leader人数：238912，规则认为是leader人数：17300，占总人数的7.2%。模型认为是leader人数：75535，占总人数的31.6%。两部分相加去重统计后leader人数：84309，占总人数的35.28%
10月过往接收过周报的一级leader人数：238912，其中有会话消息的人数：102046。规则认为是leader人数：17300，占有会话的17%。模型认为是leader人数：75535，占有会话的的74%。两部分相加去重统计后leader人数：84309，占有会话的的82.6%
