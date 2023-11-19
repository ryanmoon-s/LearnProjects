<template>
	<div>
		<el-dialog title="编辑用户信息" :visible.sync="dialogEdit.show">
			<el-form :model="formData" ref="formEdit" label-width="100px" :rules="formrules">
				<el-form-item label="日期" prop="date">
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
        <el-button @click="dialogEdit.show = false">取消</el-button>
        <el-button type="primary" @click="dialogFormEdit('formEdit')">确定</el-button>
      </div>

		</el-dialog>
	</div>
</template>

<script>
export default {
	name: 'EditUser',
  props:{
    dialogEdit:Object,
    formData:Object
  },
	data () {
    return {
      formrules:{
        date:[{required:true,message:"日期不能为空",trigger:"blur"}],
        name:[{required:true,message:"用户名不能为空",trigger:"blur"}],
        email:[{required:true,message:"邮箱不能为空",trigger:"blur"}],
      }
    }
  },
	methods: {
		dialogFormEdit(formEdit) {
			this.$refs[formEdit].validate((valid) => {
				if (valid) {
					this.$axios.put(`http://localhost:3000/data/${this.formData.id}`, this.formData).then(res => {
						this.$message({
							type: "success",
							message: "编辑信息成功"
						});
						console.log(res);
            this.dialogEdit.show = false;
            this.$emit('edit');
					})
				} else {
					console.log('error submit!!');
          return false;
				}
			})
		}
	}
}
</script>