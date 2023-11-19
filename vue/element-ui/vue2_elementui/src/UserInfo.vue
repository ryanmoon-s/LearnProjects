<template>
	<div>
		<h1>用户信息管理界面</h1>
		<el-row>
			<el-col>
				<div class="edit">
					<!-- inline inline="true"的缩写 -->
					<el-form inline>
						<el-form-item style="float: left;" label="查询用户信息:">
							<el-input v-model="keyUser" placeholder="查询所需要的内容......"></el-input>
						</el-form-item>
						<el-form-item style="float: right;">
							<!-- type="primary"说明是主要按钮，色彩什么的更突出 -->
							<el-button type="primary" size="small" icon="el-icon-edit-outline" @click="hanldeAdd">添加</el-button>
						</el-form-item>
					</el-form>
				</div>
				<div class="table">
					<!-- stripe 带斑马纹路的表格 -->
					<!-- border="true" 指定边框 -->
					<el-table stripe border="true" :data="searchUserinfo(keyUser)">
						<!-- prop用来填充对象对应的字段 -->
						<el-table-column type="index" label="序号" align="center" width="60"></el-table-column>
						<el-table-column label="日期" align="center" width="120" prop="date"></el-table-column>
						<el-table-column label="姓名" align="center" width="100" prop="name"></el-table-column>
						<el-table-column label="邮箱" align="center" width="160" prop="email"></el-table-column>
						<el-table-column label="标题" align="center" width="160" prop="title"></el-table-column>
						<el-table-column label="评价" align="center" width="200" prop="evaluate"></el-table-column>
						<el-table-column label="状态" align="center" width="160" prop="state"></el-table-column>
						<el-table-column label="操作" fixed="right">
							<!-- 非直接填充文字时，用slot-scope -->
							<template slot-scope="scope">
								<el-button size="mini" @click="handleEdit(scope.$index, scope.row)">编辑</el-button>
								<el-button size="mini" type="danger" @click="handleDelete(scope.$index, scope.row)">删除</el-button>
							</template>
						</el-table-column>
					</el-table>
				</div>
			</el-col>
		</el-row>
		<!-- 申明另外两个组件 -->
		<!-- 将dialogAdd对象，作为属性传给子组件，子组件在data:props里面申明 -->
		<!-- @update申明一个事件，子组件用emit触发事件 this.$emit('update') -->
		<AddUser :dialogAdd="dialogAdd" @add="getUserInfo"></AddUser>
		<!-- 将form对象传给子组件 -->
		<EditUser :dialogEdit="dialogEdit" :formData="formData" @edit="getUserInfo"></EditUser>
	</div>
</template>

<script>
import AddUser from './AddUser'
import EditUser from './EditUser'

export default {
	name: "info",
	data() {
		return {
			keyUser: "",
			tableData: [],
			dialogAdd:{
        show: false
      },
			dialogEdit:{
        show: false
      },
			formData:{ // 传给编辑子组件，一行记录的表单信息
        date:'',
        name:'',
        email:'',
        title:'',
        evaluate:'',
        state:''
      },
		}
	},
	methods: {
		hanldeAdd() {
			this.dialogAdd.show = true;
		},
		searchUserinfo(keyUser) {
			// 搜索用户信息
			return this.tableData.filter((user) => {
				if (user.name.includes(keyUser)) {
					return user;
				}
			})
		},
		handleEdit(index, row){
			// 编辑用户信息
      this.dialogEdit.show = true; //显示弹
      this.formData = {
        date:row.date,
        name:row.name,
        email:row.email,
        title:row.title,
        evaluate:row.evaluate,
        state:row.state,
        id:row.id
      }
    },
    handleDelete(index, row) {
      // 删除用户信息
      this.$axios.delete(`http://localhost:3000/data/${row.id}`).then(res =>{
        this.$message({
          type:"success",
          message:"删除信息成功"
        });
        this.getUserInfo();    //删除数据，更新视图
      })
    },
		// 实时从服务器拉取最新数据
		getUserInfo() {
      this.$axios.get('http://localhost:3000/data').then(res => {
        this.tableData = res.data
      });
    },
	},
	components: {
		AddUser, EditUser
	},
	// 创建页面时就加载数据
	created() {
		console.log("created ara");
		this.getUserInfo();
		console.log("created ara 2");
	}
}
</script>

<!-- scoped 只能在这个组件里面用 -->
<style scoped>
h1 {
  font-size: 30px;
  color: #333;
  text-align: center;
  margin: 0 auto;
  padding-bottom: 5px;
  border-bottom: 2px solid #409EFF;
  width: 300px
}
</style>