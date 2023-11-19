<template>
	<div class="add-dialog">
		<el-dialog title="添加用户信息" :visible.sync="dialogAdd.show">
			<!-- ref='formdong' 将此表单的信息用formdong对象表示，可在其它地方引用formdong -->
			<!-- rules="formrules" 指定表单验证规则，放在data里面 -->
			<el-form :model="formData" ref="formdong" label-width="100px" :rules="formrules">
				<el-form-item label="日期">
					<el-date-picker v-model="formData.date" type="date" placeholder="选择日期"></el-date-picker>
				</el-form-item>
				<el-form-item label="姓名">
          <el-input v-model="formData.name"></el-input>
        </el-form-item>
        <el-form-item label="邮箱">
          <el-input v-model="formData.email"></el-input>
        </el-form-item>
        <el-form-item label="标题">
          <el-input v-model="formData.title"></el-input>
        </el-form-item>
        <el-form-item label="评价">
          <el-input v-model="formData.evaluate"></el-input>
        </el-form-item>
        <el-form-item label="状态">
          <el-input v-model="formData.state"></el-input>
        </el-form-item>
			</el-form>
			<div slot="footer" class="dialog-footer">
        <el-button @click="dialogAdd.show=false">取消</el-button>
				<!-- formdong传入的是一个字符串 -->
        <el-button type="primary" @click="dialogFormAdd('formdong')">确定</el-button>
      </div>
		</el-dialog>
	</div>
</template>

<script>
export default {
	name: "AddUser",
	// 从父窗口传过来的 :dialogAdd=
	props: {
		dialogAdd: Object
	},
	data() {
		return {
			formData:{
				date:'2023-11-03',
        name:'小白',
        email:'123@qq.com',
        title:'这是一个title',
        evaluate:'还可以',
        state:'状态'
      },
			formrules:{
				// blur 失去焦点
        date:[{required:true,message:"日期不能为空",trigger:"blur"}],
        name:[{required:true,message:"用户名不能为空",trigger:"blur"}],
        email:[{required:true,message:"邮箱不能为空",trigger:"blur"}],
      }
		}
	},
	methods:{
		// formdong 表单对象
    dialogFormAdd(formdong) {
			// formdong是一个字符串，从$ref里面取出formdong表单对象
			// validate验证表单，填入一个函数，参数为是否有效
      this.$refs[formdong].validate((valid) => {
        if (valid) {
          this.$axios.post('http://localhost:3000/data', this.formData).then(res => {
            this.$message({
              type:"success",
              message:"添加信息成功"
            });
            this.dialogAdd.show = false;
            this.$emit('add'); // 向父窗口发送信号
          })
          // this.formData  = ""
        } else {
          console.log('error submit!!');
          return false;
        }
      })
    }
  }
}
</script>